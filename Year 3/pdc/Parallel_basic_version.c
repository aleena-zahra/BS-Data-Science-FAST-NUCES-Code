/*
 * Name       : Aleena Zahra
 * Student ID : 23i-2514
 * Assignment : 3 - Distributed Sensor Intelligent System
 * File       : Parallel_basic_version.c
 *
 * Description:
 *   Basic MPI parallel pipeline.
 *   - Master (rank 0): loads full dataset, partitions sensors evenly,
 *     distributes each worker's slice, collects results, final ranking.
 *   - Workers: receive their sensor slice, perform local feature
 *     extraction, local similarity, local anomaly scoring, send scores back.
 *
 * Compile : mpicc -O2 -o parallel_basic Parallel_basic_version.c -lm
 * Run     : mpirun -np <P> ./parallel_basic Dataset.csv
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

/* tuneable constants  */
#define WINDOW_SIZE      20
#define K_PAIRS          200
#define ALPHA            0.6
#define BETA             0.4
#define TOP_N            10
#define FEATURES_PER_WIN 4


typedef struct { int sensor_id; double score; } SensorScore;

/*  helpers  */
static double vec_dot(const double *a, const double *b, int n) {
    double s = 0.0;
    for (int i = 0; i < n; i++) s += a[i] * b[i];
    return s;
}
static double vec_norm(const double *a, int n) { return sqrt(vec_dot(a, a, n)); }
static double cosine_similarity(const double *a, const double *b, int n) {
    double na = vec_norm(a, n), nb = vec_norm(b, n);
    if (na < 1e-12 || nb < 1e-12) return 0.0;
    return vec_dot(a, b, n) / (na * nb);
}
static int cmp_desc(const void *a, const void *b) {
    const SensorScore *sa = (const SensorScore *)a;
    const SensorScore *sb = (const SensorScore *)b;
    return (sb->score > sa->score) - (sb->score < sa->score);
}

/*  local computation per node  */
/*
 * sensor_block : flat array [local_count * num_timesteps]
 * local_count  : sensors assigned to this rank
 * returns      : malloc'd flat feature matrix [local_count * feat_len]
 */
static double *local_feature_extraction(const double *sensor_block,
                                        int local_count, int num_timesteps,
                                        int *out_feat_len) {
    int num_windows = num_timesteps / WINDOW_SIZE;
    int fl = num_windows * FEATURES_PER_WIN;
    *out_feat_len = fl;
    double *feats = (double *)malloc((size_t)local_count * fl * sizeof(double));

    for (int s = 0; s < local_count; s++) {
        const double *ts = sensor_block + (size_t)s * num_timesteps;
        double *fv = feats + (size_t)s * fl;
        for (int w = 0; w < num_windows; w++) {
            int base = w * WINDOW_SIZE;
            double mean = 0.0, var = 0.0, energy = 0.0;
            for (int i = 0; i < WINDOW_SIZE; i++) mean += ts[base + i];
            mean /= WINDOW_SIZE;
            for (int i = 0; i < WINDOW_SIZE; i++) {
                double x = ts[base + i];
                var    += (x - mean) * (x - mean);
                energy += x * x;
            }
            var /= WINDOW_SIZE;
            fv[w * FEATURES_PER_WIN + 0] = mean;
            fv[w * FEATURES_PER_WIN + 1] = var;
            fv[w * FEATURES_PER_WIN + 2] = energy;
            fv[w * FEATURES_PER_WIN + 3] = sqrt(energy);
        }
    }
    return feats;
}

/* local anomaly scoring using local feature vectors */
static double *local_anomaly_scoring(const double *feats, int local_count,
                                     int feat_len, int first_sensor_id) {
    /* local global mean */
    double *lmean = (double *)calloc(feat_len, sizeof(double));
    for (int s = 0; s < local_count; s++)
        for (int j = 0; j < feat_len; j++)
            lmean[j] += feats[(size_t)s * feat_len + j];
    for (int j = 0; j < feat_len; j++) lmean[j] /= local_count;

    double *scores = (double *)malloc(local_count * sizeof(double));
    for (int s = 0; s < local_count; s++) {
        const double *fv = feats + (size_t)s * feat_len;
        double dev = 0.0;
        for (int j = 0; j < feat_len; j++) dev += fabs(fv[j] - lmean[j]);
        dev /= feat_len;

        int nb = (s + 1) % local_count;
        double sim = cosine_similarity(fv, feats + (size_t)nb * feat_len, feat_len);
        scores[s] = ALPHA * dev + BETA * (1.0 - sim);
    }
    free(lmean);
    return scores;
}

/*  main  */
int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double t_start = MPI_Wtime();

    const char *fname = (argc > 1) ? argv[1] : "Dataset.csv";

    int num_sensors = 0, num_timesteps = 0;
    double *full_data = NULL;   /* master only */
    int *sensor_ids   = NULL;   /* global sensor ids */

    /*  Step 2: Master loads dataset  */
    if (rank == 0) {
        printf("=== Basic Parallel Pipeline  (MPI ranks: %d) ===\n", size);
        FILE *fp = fopen(fname, "r");
        if (!fp) { MPI_Abort(MPI_COMM_WORLD, 1); }
        char line[256];
        fgets(line, sizeof(line), fp); /* header */
        int ms = -1, mt = -1;
        while (fgets(line, sizeof(line), fp)) {
            int s, t; float v;
            if (sscanf(line, "%d,%d,%f", &s, &t, &v) == 3) {
                if (s > ms) ms = s;
                if (t > mt) mt = t;
            }
        }
        num_sensors   = ms + 1;
        num_timesteps = mt + 1;
        printf("[Master] Sensors: %d | Timesteps: %d\n", num_sensors, num_timesteps);

        full_data = (double *)malloc((size_t)num_sensors * num_timesteps * sizeof(double));
        rewind(fp);
        fgets(line, sizeof(line), fp);
        while (fgets(line, sizeof(line), fp)) {
            int s, t; float v;
            if (sscanf(line, "%d,%d,%f", &s, &t, &v) == 3)
                full_data[(size_t)s * num_timesteps + t] = (double)v;
        }
        fclose(fp);
    }

    /*  Broadcast dimensions  */
    MPI_Bcast(&num_sensors,   1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&num_timesteps, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /*  Step 3: Data Partitioning  */
    int *counts  = (int *)malloc(size * sizeof(int));
    int *displs  = (int *)malloc(size * sizeof(int));
    int *id_counts = (int *)malloc(size * sizeof(int));
    int *id_displs = (int *)malloc(size * sizeof(int));
    int base_s = num_sensors / size, rem = num_sensors % size;
    for (int r = 0; r < size; r++) {
        counts[r]    = (base_s + (r < rem ? 1 : 0)) * num_timesteps;
        id_counts[r] = (base_s + (r < rem ? 1 : 0));
    }
    displs[0] = id_displs[0] = 0;
    for (int r = 1; r < size; r++) {
        displs[r]    = displs[r-1]    + counts[r-1];
        id_displs[r] = id_displs[r-1] + id_counts[r-1];
    }
    int local_count = id_counts[rank];

    /*  Step 4: Data Distribution  */
    double *local_block = (double *)malloc((size_t)local_count * num_timesteps * sizeof(double));
    MPI_Scatterv(full_data, counts, displs, MPI_DOUBLE,
                 local_block, local_count * num_timesteps, MPI_DOUBLE,
                 0, MPI_COMM_WORLD);

    /* track which sensor IDs we own */
    int first_id = id_displs[rank];

    /*  Step 5: Local Feature Extraction  */
    int feat_len = 0;
    double *local_feats = local_feature_extraction(local_block, local_count,
                                                   num_timesteps, &feat_len);
    free(local_block);

    /*  Step 6: Local Similarity (within partition only)  */
    /* (printed for info; used implicitly in scoring below) */

    /*  Step 5: Local Anomaly Scoring  */
    double *local_scores = local_anomaly_scoring(local_feats, local_count,
                                                 feat_len, first_id);
    free(local_feats);

    /*  Step 6 (Result Collection): Send scores back to master  */
    double *all_scores = NULL;
    int    *all_ids    = NULL;
    if (rank == 0) {
        all_scores = (double *)malloc(num_sensors * sizeof(double));
        all_ids    = (int    *)malloc(num_sensors * sizeof(int));
    }
    MPI_Gatherv(local_scores, local_count, MPI_DOUBLE,
                all_scores, id_counts, id_displs, MPI_DOUBLE,
                0, MPI_COMM_WORLD);
    free(local_scores);

    /*  Step 7: Final Ranking (Master)  */
    if (rank == 0) {
        SensorScore *ranked = (SensorScore *)malloc(num_sensors * sizeof(SensorScore));
        for (int s = 0; s < num_sensors; s++) {
            ranked[s].sensor_id = s;
            ranked[s].score     = all_scores[s];
        }
        qsort(ranked, num_sensors, sizeof(SensorScore), cmp_desc);

        printf("\n╔══════════════════════════════════════════╗\n");
        printf("║      TOP %2d ANOMALOUS SENSORS (Basic)    ║\n", TOP_N);
        printf("╠═══════════╦══════════════════════════════╣\n");
        printf("║   Rank    ║  Sensor ID  │  Anomaly Score ║\n");
        printf("╠═══════════╬══════════════════════════════╣\n");
        for (int i = 0; i < TOP_N; i++)
            printf("║    %3d    ║   %6d    │   %12.6f  ║\n",
                   i+1, ranked[i].sensor_id, ranked[i].score);
        printf("╚═══════════╩══════════════════════════════╝\n\n");

        free(ranked); free(all_scores); free(all_ids); free(full_data);
    }

    free(counts); free(displs); free(id_counts); free(id_displs);

    double t_end = MPI_Wtime();
    if (rank == 0)
        printf("[Timing] Basic parallel execution time (%d ranks): %.4f seconds\n",
               size, t_end - t_start);

    MPI_Finalize();
    return 0;
}

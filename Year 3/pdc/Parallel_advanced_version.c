/*
 * Name       : Aleena Zahra
 * Student ID : 23i-2514
 * Assignment : 3 - Distributed Sensor Intelligent System
 * File       : Parallel_advanced_version.c
 *
 * Description:
 *   Advanced MPI parallel pipeline with:
 *   - Structured even partitioning (Step 1)
 *   - Coordinated simultaneous distribution via MPI_Scatterv (Step 2)
 *   - Independent local feature computation (Step 3)
 *   - Partial feature sharing: each node shares with direct neighbours (Step 4)
 *   - Cross-partition similarity (local + remote sensors) (Step 5)
 *   - Global aggregation: each node contributes to global anomaly scores (Step 6)
 *   - Master collects and displays Top-10 (Step 7)
 *
 * Compile : mpicc -O2 -o parallel_advanced Parallel_advanced_version.c -lm
 * Run     : mpirun -np <P> ./parallel_advanced Dataset.csv
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

/*  tuneable constants  */
#define WINDOW_SIZE       20
#define ALPHA             0.6
#define BETA              0.4
#define TOP_N             10
#define FEATURES_PER_WIN  4
#define SHARE_SUBSET      50   /* sensors shared with each neighbour (partial) */


typedef struct { int sensor_id; double score; } SensorScore;

/*  math helpers  */
static double vec_dot(const double *a, const double *b, int n) {
    double s = 0.0;
    for (int i = 0; i < n; i++) s += a[i] * b[i];
    return s;
}
static double vec_norm(const double *a, int n) { return sqrt(vec_dot(a,a,n)); }
static double cosine_sim(const double *a, const double *b, int n) {
    double na = vec_norm(a,n), nb = vec_norm(b,n);
    if (na < 1e-12 || nb < 1e-12) return 0.0;
    return vec_dot(a,b,n) / (na * nb);
}
static int cmp_desc(const void *a, const void *b) {
    const SensorScore *sa = (const SensorScore *)a;
    const SensorScore *sb = (const SensorScore *)b;
    return (sb->score > sa->score) - (sb->score < sa->score);
}

/*  feature extraction  */
static double *extract_features(const double *block, int count,
                                int timesteps, int *out_fl) {
    int nw = timesteps / WINDOW_SIZE;
    int fl = nw * FEATURES_PER_WIN;
    *out_fl = fl;
    double *feats = (double *)malloc((size_t)count * fl * sizeof(double));
    for (int s = 0; s < count; s++) {
        const double *ts = block + (size_t)s * timesteps;
        double *fv = feats + (size_t)s * fl;
        for (int w = 0; w < nw; w++) {
            int base = w * WINDOW_SIZE;
            double mean = 0.0, var = 0.0, energy = 0.0;
            for (int i = 0; i < WINDOW_SIZE; i++) mean += ts[base+i];
            mean /= WINDOW_SIZE;
            for (int i = 0; i < WINDOW_SIZE; i++) {
                double x = ts[base+i];
                var    += (x - mean)*(x - mean);
                energy += x*x;
            }
            var /= WINDOW_SIZE;
            fv[w*FEATURES_PER_WIN+0] = mean;
            fv[w*FEATURES_PER_WIN+1] = var;
            fv[w*FEATURES_PER_WIN+2] = energy;
            fv[w*FEATURES_PER_WIN+3] = sqrt(energy);
        }
    }
    return feats;
}

/*  anomaly scoring  */
/*
 * local_feats   : [local_count x feat_len]  — own sensors
 * remote_feats  : [remote_count x feat_len] — received from neighbour
 * global_mean   : [feat_len]                — broadcast from master
 */
static double *compute_scores(const double *local_feats, int local_count,
                               const double *remote_feats, int remote_count,
                               const double *global_mean, int feat_len) {
    double *scores = (double *)malloc(local_count * sizeof(double));
    for (int s = 0; s < local_count; s++) {
        const double *fv = local_feats + (size_t)s * feat_len;

        /* deviation from global mean */
        double dev = 0.0;
        for (int j = 0; j < feat_len; j++) dev += fabs(fv[j] - global_mean[j]);
        dev /= feat_len;

        /* cross-partition similarity: compare with remote sensors if available */
        double sim = 0.0;
        if (remote_count > 0) {
            int ri = s % remote_count;
            sim = cosine_sim(fv, remote_feats + (size_t)ri * feat_len, feat_len);
        } else {
            /* fallback: neighbour within local partition */
            int nb = (s + 1) % local_count;
            sim = cosine_sim(fv, local_feats + (size_t)nb * feat_len, feat_len);
        }

        scores[s] = ALPHA * dev + BETA * (1.0 - sim);
    }
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
    double *full_data = NULL;

    /* ══════════════════════════════════════════════════
     * Step 2: Master loads & initialises
     * ══════════════════════════════════════════════════ */
    if (rank == 0) {
        printf("=== Advanced Parallel Pipeline  (MPI ranks: %d) ===\n", size);
        FILE *fp = fopen(fname, "r");
        if (!fp) { perror("fopen"); MPI_Abort(MPI_COMM_WORLD, 1); }
        char line[256];
        fgets(line, sizeof(line), fp);
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

    /* broadcast dimensions */
    MPI_Bcast(&num_sensors,   1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&num_timesteps, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /* ══════════════════════════════════════════════════
     * Step 1: Structured Partitioning — even split
     * ══════════════════════════════════════════════════ */
    int *id_counts = (int *)malloc(size * sizeof(int));
    int *id_displs = (int *)malloc(size * sizeof(int));
    int *dt_counts = (int *)malloc(size * sizeof(int));
    int *dt_displs = (int *)malloc(size * sizeof(int));
    int base_s = num_sensors / size, rem = num_sensors % size;
    for (int r = 0; r < size; r++) {
        id_counts[r] = base_s + (r < rem ? 1 : 0);
        dt_counts[r] = id_counts[r] * num_timesteps;
    }
    id_displs[0] = dt_displs[0] = 0;
    for (int r = 1; r < size; r++) {
        id_displs[r] = id_displs[r-1] + id_counts[r-1];
        dt_displs[r] = dt_displs[r-1] + dt_counts[r-1];
    }
    int local_count = id_counts[rank];
    int first_id    = id_displs[rank];

    /* ══════════════════════════════════════════════════
     * Step 2: Coordinated Simultaneous Distribution
     *         All ranks receive data at the same time via MPI_Scatterv
     * ══════════════════════════════════════════════════ */
    double *local_block = (double *)malloc((size_t)local_count * num_timesteps * sizeof(double));
    MPI_Scatterv(full_data, dt_counts, dt_displs, MPI_DOUBLE,
                 local_block, local_count * num_timesteps, MPI_DOUBLE,
                 0, MPI_COMM_WORLD);
    if (rank == 0) { free(full_data); full_data = NULL; }

    /* ══════════════════════════════════════════════════
     * Step 3: Independent Feature Computation
     * ══════════════════════════════════════════════════ */
    int feat_len = 0;
    double *local_feats = extract_features(local_block, local_count,
                                           num_timesteps, &feat_len);
    free(local_block);
    printf("[Rank %d] Feature extraction done. local_count=%d feat_len=%d\n",
           rank, local_count, feat_len);

    /* ══════════════════════════════════════════════════
     * Step 4: Partial Feature Sharing (ring exchange)
     *         Each node sends a subset of its feature vectors to its
     *         right neighbour and receives from its left neighbour.
     * ══════════════════════════════════════════════════ */
    int share_n = (local_count < SHARE_SUBSET) ? local_count : SHARE_SUBSET;
    int share_bytes = share_n * feat_len;

    /* send first share_n rows to right neighbour; receive from left */
    double *send_buf = local_feats;                          /* first share_n rows */
    double *recv_buf = (double *)malloc((size_t)share_bytes * sizeof(double));

    int left  = (rank - 1 + size) % size;
    int right = (rank + 1) % size;

    MPI_Sendrecv(send_buf, share_bytes, MPI_DOUBLE, right, 10,
                 recv_buf, share_bytes, MPI_DOUBLE, left,  10,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    /* ══════════════════════════════════════════════════
     * Step 5 / Step 6: Cross-Partition Similarity &
     *                  Global Anomaly Scoring
     *
     *   Each node computes its local anomaly scores using:
     *     - its own feature vectors
     *     - remote feature vectors received from neighbour
     *   Then master gathers and computes global mean for a
     *   refined second pass.
     * ══════════════════════════════════════════════════ */

    /* First: compute a local global mean and share across all ranks */
    double *local_sum = (double *)calloc(feat_len, sizeof(double));
    for (int s = 0; s < local_count; s++)
        for (int j = 0; j < feat_len; j++)
            local_sum[j] += local_feats[(size_t)s * feat_len + j];

    double *global_sum = (double *)calloc(feat_len, sizeof(double));
    MPI_Allreduce(local_sum, global_sum, feat_len, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    free(local_sum);

    double *global_mean = (double *)malloc(feat_len * sizeof(double));
    for (int j = 0; j < feat_len; j++) global_mean[j] = global_sum[j] / num_sensors;
    free(global_sum);

    /* Score using global mean + cross-partition remote sensors */
    double *local_scores = compute_scores(local_feats, local_count,
                                          recv_buf, share_n,
                                          global_mean, feat_len);
    free(local_feats);
    free(recv_buf);
    free(global_mean);

    /* ══════════════════════════════════════════════════
     * Step 7: Final Ranking — Master collects all scores
     * ══════════════════════════════════════════════════ */
    double *all_scores = NULL;
    if (rank == 0) all_scores = (double *)malloc(num_sensors * sizeof(double));

    MPI_Gatherv(local_scores, local_count, MPI_DOUBLE,
                all_scores, id_counts, id_displs, MPI_DOUBLE,
                0, MPI_COMM_WORLD);
    free(local_scores);

    if (rank == 0) {
        SensorScore *ranked = (SensorScore *)malloc(num_sensors * sizeof(SensorScore));
        for (int s = 0; s < num_sensors; s++) {
            ranked[s].sensor_id = s;
            ranked[s].score     = all_scores[s];
        }
        qsort(ranked, num_sensors, sizeof(SensorScore), cmp_desc);

        printf("\n╔══════════════════════════════════════════╗\n");
        printf("║    TOP %2d ANOMALOUS SENSORS (Advanced)   ║\n", TOP_N);
        printf("╠═══════════╦══════════════════════════════╣\n");
        printf("║   Rank    ║  Sensor ID  │  Anomaly Score ║\n");
        printf("╠═══════════╬══════════════════════════════╣\n");
        for (int i = 0; i < TOP_N; i++)
            printf("║    %3d    ║   %6d    │   %12.6f  ║\n",
                   i+1, ranked[i].sensor_id, ranked[i].score);
        printf("╚═══════════╩══════════════════════════════╝\n\n");

        free(ranked); free(all_scores);
    }

    free(id_counts); free(id_displs); free(dt_counts); free(dt_displs);

    double t_end = MPI_Wtime();
    if (rank == 0)
        printf("[Timing] Advanced parallel execution time (%d ranks): %.4f seconds\n",
               size, t_end - t_start);

    MPI_Finalize();
    return 0;
}

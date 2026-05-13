/*
 * Name       : Aleena Zahra
 * Student ID : 23i-2514
 * Assignment : 3 - Distributed Sensor Intelligent System
 * File       : Parallel_basic_version.c
 *
 * Compile : mpicc -O2 -o par_basic Parallel_basic_version.c -lm
 * Run     : mpirun -np <P> ./par_basic Dataset.csv
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

#define WINDOW_SIZE      20
#define K_PAIRS          200
#define ALPHA            0.6
#define BETA             0.4
#define TOP_N            10
#define FEATURES_PER_WIN 4

typedef struct { int sensor_id; double score; } SensorScore;

static double vec_dot(const double *a, const double *b, int n) {
    double s = 0.0;
    for (int i = 0; i < n; i++) s += a[i] * b[i];
    return s;
}
static double vec_norm(const double *a, int n) { return sqrt(vec_dot(a,a,n)); }
static double cosine_sim(const double *a, const double *b, int n) {
    double na = vec_norm(a,n), nb = vec_norm(b,n);
    if (na < 1e-12 || nb < 1e-12) return 0.0;
    return vec_dot(a,b,n) / (na*nb);
}
static int cmp_desc(const void *a, const void *b) {
    const SensorScore *sa = (const SensorScore *)a;
    const SensorScore *sb = (const SensorScore *)b;
    return (sb->score > sa->score) - (sb->score < sa->score);
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double t_start = MPI_Wtime();
    double ts, te;

    const char *fname = (argc > 1) ? argv[1] : "Dataset.csv";
    int num_sensors = 0, num_timesteps = 0;
    double *full_data = NULL;

    /* ═══════════════════════════════════════════════════
     * STEP 1: DATASET LOADING  (Master only)
     * ═══════════════════════════════════════════════════ */
    ts = MPI_Wtime();
    if (rank == 0) {
        printf("\n====================================================\n");
        printf("   BASIC PARALLEL SENSOR INTELLIGENCE PIPELINE\n");
        printf("   MPI Ranks: %d\n", size);
        printf("====================================================\n");

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
    MPI_Bcast(&num_sensors,   1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&num_timesteps, 1, MPI_INT, 0, MPI_COMM_WORLD);
    te = MPI_Wtime();

    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║           STEP 1: DATASET LOADING                ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  File             : %-28s ║\n", fname);
        printf("║  Total Sensors    : %-28d ║\n", num_sensors);
        printf("║  Total Timesteps  : %-28d ║\n", num_timesteps);
        printf("║  Total Data Rows  : %-28d ║\n", num_sensors * num_timesteps);
        printf("║  Loaded by        : Master Node (Rank 0)         ║\n");
        printf("║  Step Time        : %-25.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    /* ═══════════════════════════════════════════════════
     * STEP 2: DATA PARTITIONING
     * ═══════════════════════════════════════════════════ */
    ts = MPI_Wtime();
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
    te = MPI_Wtime();

    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║           STEP 2: DATA PARTITIONING              ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Total Sensors    : %-28d ║\n", num_sensors);
        printf("║  Total MPI Ranks  : %-28d ║\n", size);
        printf("║  Sensors per Rank : ~%-27d ║\n", base_s);
        printf("║                                                  ║\n");
        printf("║  Rank   First Sensor   Last Sensor   Count       ║\n");
        printf("║  ----   ------------   -----------   -----       ║\n");
        for (int r = 0; r < size; r++)
            printf("║  %-4d   %-12d   %-11d   %-5d       ║\n",
                   r, id_displs[r],
                   id_displs[r] + id_counts[r] - 1,
                   id_counts[r]);
        printf("║  Step Time: %-34.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    /* ═══════════════════════════════════════════════════
     * STEP 3: DATA DISTRIBUTION via MPI_Scatterv
     * ═══════════════════════════════════════════════════ */
    ts = MPI_Wtime();
    double *local_block = (double *)malloc((size_t)local_count * num_timesteps * sizeof(double));
    MPI_Scatterv(full_data, dt_counts, dt_displs, MPI_DOUBLE,
                 local_block, local_count * num_timesteps, MPI_DOUBLE,
                 0, MPI_COMM_WORLD);
    if (rank == 0) { free(full_data); full_data = NULL; }
    te = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║           STEP 3: DATA DISTRIBUTION              ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Method : MPI_Scatterv (Master -> All Workers)   ║\n");
        printf("║  Guarantee: No overlap, no missing data          ║\n");
        printf("║                                                  ║\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    for (int r = 0; r < size; r++) {
        if (rank == r) {
            printf("║  Rank %-2d received sensors %4d to %4d  (%4d)  ║\n",
                   rank, first_id, first_id + local_count - 1, local_count);
            fflush(stdout);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    if (rank == 0) {
        printf("║  Step Time: %-34.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    /* ═══════════════════════════════════════════════════
     * STEP 4: SLIDING WINDOW FEATURE EXTRACTION
     * Each rank independently computes features
     * ═══════════════════════════════════════════════════ */
    ts = MPI_Wtime();
    int num_windows = num_timesteps / WINDOW_SIZE;
    int feat_len    = num_windows * FEATURES_PER_WIN;

    double *local_feats = (double *)malloc((size_t)local_count * feat_len * sizeof(double));
    for (int s = 0; s < local_count; s++) {
        const double *tss = local_block + (size_t)s * num_timesteps;
        double *fv = local_feats + (size_t)s * feat_len;
        for (int w = 0; w < num_windows; w++) {
            int base = w * WINDOW_SIZE;
            double mean = 0.0, var = 0.0, energy = 0.0;
            for (int i = 0; i < WINDOW_SIZE; i++) mean += tss[base+i];
            mean /= WINDOW_SIZE;
            for (int i = 0; i < WINDOW_SIZE; i++) {
                double x = tss[base+i];
                var    += (x-mean)*(x-mean);
                energy += x*x;
            }
            var /= WINDOW_SIZE;
            fv[w*FEATURES_PER_WIN+0] = mean;
            fv[w*FEATURES_PER_WIN+1] = var;
            fv[w*FEATURES_PER_WIN+2] = energy;
            fv[w*FEATURES_PER_WIN+3] = sqrt(energy);
        }
    }
    free(local_block);
    te = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║  STEP 4: SLIDING WINDOW FEATURE EXTRACTION       ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Window Size         : %-25d ║\n", WINDOW_SIZE);
        printf("║  Windows per Sensor  : %-25d ║\n", num_windows);
        printf("║  Features per Window : 4 (Mean,Var,Energy,Mag)   ║\n");
        printf("║  Feature Vector Len  : %-25d ║\n", feat_len);
        printf("║  Computed by         : Each rank independently   ║\n");
        printf("║                                                  ║\n");
        printf("║  Sample (Rank 0, sensor 0, window 0):            ║\n");
        printf("║    Mean      = %10.4f                        ║\n", local_feats[0]);
        printf("║    Variance  = %10.4f                        ║\n", local_feats[1]);
        printf("║    Energy    = %10.4f                        ║\n", local_feats[2]);
        printf("║    Magnitude = %10.4f                        ║\n", local_feats[3]);
        printf("║                                                  ║\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    for (int r = 0; r < size; r++) {
        if (rank == r) {
            printf("║  Rank %-2d: extracted features for %4d sensors    ║\n",
                   rank, local_count);
            fflush(stdout);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    if (rank == 0) {
        printf("║  Step Time: %-34.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    /* ═══════════════════════════════════════════════════
     * STEP 4b: FEATURE VECTOR CONSTRUCTION
     * ═══════════════════════════════════════════════════ */
    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║      STEP 4b: FEATURE VECTOR CONSTRUCTION        ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  All window features concatenated per sensor:    ║\n");
        printf("║  [m1,v1,e1,mag1, m2,v2,e2,mag2, ... mN,vN,...]  ║\n");
        printf("║                                                  ║\n");
        printf("║  Sample Rank 0, Sensor 0 (first 8 values):      ║\n");
        printf("║  ");
        for (int j = 0; j < 8 && j < feat_len; j++)
            printf("%7.2f ", local_feats[j]);
        printf("  ║\n");
        printf("║                                                  ║\n");
        for (int r = 0; r < size; r++)
            printf("║  Rank %-2d: %4d sensors x %3d features each        ║\n",
                   r, id_counts[r], feat_len);
        printf("╚══════════════════════════════════════════════════╝\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    /* ═══════════════════════════════════════════════════
     * STEP 5: LOCAL SIMILARITY COMPUTATION
     * Within each partition only (no cross-node)
     * ═══════════════════════════════════════════════════ */
    ts = MPI_Wtime();
    double sim_avg = 0.0, sim_min = 1.0, sim_max = 0.0;
    int samp_a = 0, samp_b = 0;
    double samp_s = 0.0;

    srand(42 + first_id);
    int npairs = (local_count > 1) ? K_PAIRS : 0;
    double sim_total = 0.0;
    for (int k = 0; k < npairs; k++) {
        int a = rand() % local_count;
        int b = rand() % local_count;
        if (a == b) b = (b+1) % local_count;
        double s = cosine_sim(local_feats + (size_t)a*feat_len,
                              local_feats + (size_t)b*feat_len, feat_len);
        sim_total += s;
        if (s < sim_min) sim_min = s;
        if (s > sim_max) sim_max = s;
        if (k == 0) { samp_a = first_id+a; samp_b = first_id+b; samp_s = s; }
    }
    sim_avg = (npairs > 0) ? sim_total / npairs : 0.0;
    te = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║     STEP 5: LOCAL SIMILARITY COMPUTATION         ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Method : Cosine Similarity                      ║\n");
        printf("║  Scope  : Within each partition only             ║\n");
        printf("║  Pairs per rank : %-30d ║\n", K_PAIRS);
        printf("║                                                  ║\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    for (int r = 0; r < size; r++) {
        if (rank == r) {
            printf("║  Rank %-2d | Avg=%.4f  Min=%.4f  Max=%.4f    ║\n",
                   rank, sim_avg, sim_min, sim_max);
            printf("║    e.g. Sensor %4d <-> %4d  similarity=%.4f  ║\n",
                   samp_a, samp_b, samp_s);
            fflush(stdout);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    if (rank == 0) {
        printf("║  Step Time: %-34.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    /* ═══════════════════════════════════════════════════
     * STEP 6: LOCAL ANOMALY SCORING
     * ═══════════════════════════════════════════════════ */
    ts = MPI_Wtime();
    double *lmean = (double *)calloc(feat_len, sizeof(double));
    for (int s = 0; s < local_count; s++)
        for (int j = 0; j < feat_len; j++)
            lmean[j] += local_feats[(size_t)s*feat_len + j];
    for (int j = 0; j < feat_len; j++) lmean[j] /= local_count;

    double *local_scores = (double *)malloc(local_count * sizeof(double));
    double sc_min = 1e18, sc_max = -1e18;
    for (int s = 0; s < local_count; s++) {
        const double *fv = local_feats + (size_t)s*feat_len;
        double dev = 0.0;
        for (int j = 0; j < feat_len; j++) dev += fabs(fv[j] - lmean[j]);
        dev /= feat_len;
        int nb = (s+1) % local_count;
        double sim = cosine_sim(fv, local_feats + (size_t)nb*feat_len, feat_len);
        local_scores[s] = ALPHA * dev + BETA * (1.0 - sim);
        if (local_scores[s] < sc_min) sc_min = local_scores[s];
        if (local_scores[s] > sc_max) sc_max = local_scores[s];
    }
    free(lmean);
    free(local_feats);
    te = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║          STEP 6: LOCAL ANOMALY SCORING           ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Score = %.1f*Deviation + %.1f*(1 - Similarity)    ║\n", ALPHA, BETA);
        printf("║  Each rank scores its own sensors independently  ║\n");
        printf("║                                                  ║\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    for (int r = 0; r < size; r++) {
        if (rank == r) {
            printf("║  Rank %-2d | %4d sensors | Score [%7.2f, %7.2f] ║\n",
                   rank, local_count, sc_min, sc_max);
            printf("║    Sensor %-4d score = %.4f                     ║\n",
                   first_id, local_scores[0]);
            if (local_count > 1)
                printf("║    Sensor %-4d score = %.4f                     ║\n",
                       first_id+1, local_scores[1]);
            fflush(stdout);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    if (rank == 0) {
        printf("║  Step Time: %-34.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    /* ═══════════════════════════════════════════════════
     * STEP 7: RESULT COLLECTION (workers -> master)
     * ═══════════════════════════════════════════════════ */
    ts = MPI_Wtime();
    double *all_scores = NULL;
    if (rank == 0)
        all_scores = (double *)malloc(num_sensors * sizeof(double));
    MPI_Gatherv(local_scores, local_count, MPI_DOUBLE,
                all_scores, id_counts, id_displs, MPI_DOUBLE,
                0, MPI_COMM_WORLD);
    free(local_scores);
    te = MPI_Wtime();

    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║          STEP 7: RESULT COLLECTION               ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Method : MPI_Gatherv (all workers -> master)    ║\n");
        printf("║  Master collected %4d anomaly scores             ║\n", num_sensors);
        printf("║  Step Time: %-34.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    /* ═══════════════════════════════════════════════════
     * STEP 8: FINAL RANKING (master only)
     * ═══════════════════════════════════════════════════ */
    if (rank == 0) {
        ts = MPI_Wtime();
        SensorScore *ranked = (SensorScore *)malloc(num_sensors * sizeof(SensorScore));
        for (int s = 0; s < num_sensors; s++) {
            ranked[s].sensor_id = s;
            ranked[s].score     = all_scores[s];
        }
        qsort(ranked, num_sensors, sizeof(SensorScore), cmp_desc);
        te = MPI_Wtime();

        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║      STEP 8: FINAL RANKING  (Master Node)        ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  All %4d sensor scores sorted by anomaly score   ║\n", num_sensors);
        printf("║  Step Time: %-34.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");

        printf("\n╔════════╦══════════════╦═══════════════════════════╗\n");
        printf("║        TOP %2d ANOMALOUS SENSORS  (Basic)          ║\n", TOP_N);
        printf("╠════════╦══════════════╦═══════════════════════════╣\n");
        printf("║  Rank  ║  Sensor ID   ║      Anomaly Score        ║\n");
        printf("╠════════╬══════════════╬═══════════════════════════╣\n");
        for (int i = 0; i < TOP_N; i++)
            printf("║  %4d  ║   %6d     ║       %15.6f       ║\n",
                   i+1, ranked[i].sensor_id, ranked[i].score);
        printf("╚════════╩══════════════╩═══════════════════════════╝\n");

        free(ranked);
        free(all_scores);
    }

    free(id_counts); free(id_displs); free(dt_counts); free(dt_displs);

    MPI_Barrier(MPI_COMM_WORLD);
    double t_end = MPI_Wtime();
    if (rank == 0) {
        printf("\n====================================================\n");
        printf("  TOTAL Basic Parallel Time (%d ranks): %.4f sec\n",
               size, t_end - t_start);
        printf("====================================================\n\n");
    }

    MPI_Finalize();
    return 0;
}
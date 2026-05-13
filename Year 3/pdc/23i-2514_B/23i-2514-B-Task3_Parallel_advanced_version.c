/*
 * Name       : Aleena Zahra
 * Student ID : 23i-2514
 * Assignment : 3 - Distributed Sensor Intelligent System
 * File       : Parallel_advanced_version.c
 *
 * Compile : mpicc -O2 -o par_adv Parallel_advanced_version.c -lm
 * Run     : mpirun -np <P> ./par_adv Dataset.csv
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

#define WINDOW_SIZE      20
#define ALPHA            0.6
#define BETA             0.4
#define TOP_N            10
#define FEATURES_PER_WIN 4
#define SHARE_SUBSET     50

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
        printf("  ADVANCED PARALLEL SENSOR INTELLIGENCE PIPELINE\n");
        printf("  MPI Ranks: %d\n", size);
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
     * STEP 2: STRUCTURED PARTITIONING (even split)
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
        printf("║        STEP 2: STRUCTURED PARTITIONING           ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Strategy : Even split across all ranks          ║\n");
        printf("║  Total Sensors   : %-29d ║\n", num_sensors);
        printf("║  Total Ranks     : %-29d ║\n", size);
        printf("║  Base per Rank   : %-29d ║\n", base_s);
        printf("║                                                  ║\n");
        printf("║  Rank   First Sensor   Last Sensor    Count      ║\n");
        printf("║  ----   ------------   -----------    -----      ║\n");
        for (int r = 0; r < size; r++)
            printf("║  %-4d   %-12d   %-11d    %-5d      ║\n",
                   r, id_displs[r],
                   id_displs[r] + id_counts[r] - 1,
                   id_counts[r]);
        printf("║  Step Time: %-34.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    /* ═══════════════════════════════════════════════════
     * STEP 3: COORDINATED DISTRIBUTION (all ranks simultaneously)
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
        printf("║      STEP 3: COORDINATED DATA DISTRIBUTION       ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Method : MPI_Scatterv                           ║\n");
        printf("║  All ranks receive data simultaneously           ║\n");
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
     * STEP 4: INDEPENDENT FEATURE COMPUTATION
     * Each rank: sliding window -> feature vector
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
        printf("║    STEP 4: INDEPENDENT FEATURE COMPUTATION       ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Sliding Window Size  : %-24d ║\n", WINDOW_SIZE);
        printf("║  Windows per Sensor   : %-24d ║\n", num_windows);
        printf("║  Features per Window  : 4 (Mean,Var,Energy,Mag)  ║\n");
        printf("║  Feature Vector Len   : %-24d ║\n", feat_len);
        printf("║  Computed by          : Each rank independently  ║\n");
        printf("║                                                  ║\n");
        printf("║  Feature Vector Format per Sensor:               ║\n");
        printf("║  [m1,v1,e1,mag1, m2,v2,e2,mag2, ..., mN,vN,...] ║\n");
        printf("║                                                  ║\n");
        printf("║  Sample (Rank 0, sensor 0, window 0):            ║\n");
        printf("║    Mean      = %10.4f                        ║\n", local_feats[0]);
        printf("║    Variance  = %10.4f                        ║\n", local_feats[1]);
        printf("║    Energy    = %10.4f                        ║\n", local_feats[2]);
        printf("║    Magnitude = %10.4f                        ║\n", local_feats[3]);
        printf("║                                                  ║\n");
        printf("║  Sample vector (first 8 values, Rank 0):         ║\n");
        printf("║  ");
        for (int j = 0; j < 8 && j < feat_len; j++)
            printf("%7.2f ", local_feats[j]);
        printf("  ║\n");
        printf("║                                                  ║\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    for (int r = 0; r < size; r++) {
        if (rank == r) {
            printf("║  Rank %-2d: built feature vectors for %4d sensors ║\n",
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
     * STEP 5: FEATURE SHARING ACROSS NODES (Partial)
     * Ring exchange: each rank sends SHARE_SUBSET feature
     * vectors to right neighbour, receives from left neighbour
     * ═══════════════════════════════════════════════════ */
    ts = MPI_Wtime();
    int share_n     = (local_count < SHARE_SUBSET) ? local_count : SHARE_SUBSET;
    int share_elems = share_n * feat_len;

    double *recv_feats = (double *)malloc((size_t)share_elems * sizeof(double));
    int left  = (rank - 1 + size) % size;
    int right = (rank + 1) % size;

    /* send my first share_n sensors' features to right; receive from left */
    MPI_Sendrecv(local_feats,  share_elems, MPI_DOUBLE, right, 10,
                 recv_feats,   share_elems, MPI_DOUBLE, left,  10,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int recv_from_rank = left;
    int recv_first_id  = id_displs[left];
    te = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║      STEP 5: FEATURE SHARING ACROSS NODES        ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Strategy   : Partial Sharing (ring exchange)    ║\n");
        printf("║  Share size : %d sensors per rank               ║\n", share_n);
        printf("║  Method     : MPI_Sendrecv (non-blocking ring)   ║\n");
        printf("║                                                  ║\n");
        printf("║  Ring topology:                                  ║\n");
        for (int r = 0; r < size; r++)
            printf("║    Rank %-2d  ->  sends to Rank %-2d               ║\n",
                   r, (r+1) % size);
        printf("║                                                  ║\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    for (int r = 0; r < size; r++) {
        if (rank == r) {
            printf("║  Rank %-2d: sent %3d vecs to Rank %-2d,            ║\n",
                   rank, share_n, right);
            printf("║           got %3d vecs from Rank %-2d             ║\n",
                   share_n, recv_from_rank);
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
     * STEP 6: CROSS-PARTITION SIMILARITY
     * Each rank computes similarity between its local
     * sensors AND the remote sensors it received
     * ═══════════════════════════════════════════════════ */
    ts = MPI_Wtime();
    double local_sim_sum = 0.0, local_sim_min = 1.0, local_sim_max = 0.0;
    double cross_sim_sum = 0.0, cross_sim_min = 1.0, cross_sim_max = 0.0;
    int    local_npairs = 0, cross_npairs = 0;

    /* local similarity (within own partition) */
    srand(42 + first_id);
    for (int k = 0; k < 100 && local_count > 1; k++) {
        int a = rand() % local_count;
        int b = rand() % local_count;
        if (a == b) b = (b+1) % local_count;
        double s = cosine_sim(local_feats + (size_t)a*feat_len,
                              local_feats + (size_t)b*feat_len, feat_len);
        local_sim_sum += s;
        if (s < local_sim_min) local_sim_min = s;
        if (s > local_sim_max) local_sim_max = s;
        local_npairs++;
    }

    /* cross-partition similarity (local vs remote) */
    for (int a = 0; a < local_count && a < 100; a++) {
        int b = a % share_n;
        double s = cosine_sim(local_feats + (size_t)a*feat_len,
                              recv_feats  + (size_t)b*feat_len, feat_len);
        cross_sim_sum += s;
        if (s < cross_sim_min) cross_sim_min = s;
        if (s > cross_sim_max) cross_sim_max = s;
        cross_npairs++;
    }
    te = MPI_Wtime();

    double local_sim_avg = (local_npairs > 0) ? local_sim_sum / local_npairs : 0.0;
    double cross_sim_avg = (cross_npairs > 0) ? cross_sim_sum / cross_npairs : 0.0;

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║      STEP 6: CROSS-PARTITION SIMILARITY          ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Method: Cosine Similarity                       ║\n");
        printf("║  Scope : Local sensors + Remote (received) sensors║\n");
        printf("║                                                  ║\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    for (int r = 0; r < size; r++) {
        if (rank == r) {
            printf("║  Rank %-2d LOCAL  pairs=%3d avg=%.4f [%.4f,%.4f] ║\n",
                   rank, local_npairs, local_sim_avg, local_sim_min, local_sim_max);
            printf("║  Rank %-2d CROSS  pairs=%3d avg=%.4f [%.4f,%.4f] ║\n",
                   rank, cross_npairs, cross_sim_avg, cross_sim_min, cross_sim_max);
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
     * STEP 7: GLOBAL AGGREGATION
     * MPI_Allreduce to compute true global mean across
     * all ranks, then each rank scores with global mean
     * ═══════════════════════════════════════════════════ */
    ts = MPI_Wtime();
    double *local_sum = (double *)calloc(feat_len, sizeof(double));
    for (int s = 0; s < local_count; s++)
        for (int j = 0; j < feat_len; j++)
            local_sum[j] += local_feats[(size_t)s*feat_len + j];

    double *global_sum = (double *)calloc(feat_len, sizeof(double));
    MPI_Allreduce(local_sum, global_sum, feat_len, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    free(local_sum);

    double *global_mean = (double *)malloc(feat_len * sizeof(double));
    for (int j = 0; j < feat_len; j++)
        global_mean[j] = global_sum[j] / num_sensors;
    free(global_sum);

    /* Now score each local sensor using global mean + cross-partition similarity */
    double *local_scores = (double *)malloc(local_count * sizeof(double));
    double sc_min = 1e18, sc_max = -1e18;

    for (int s = 0; s < local_count; s++) {
        const double *fv = local_feats + (size_t)s*feat_len;

        /* deviation from global mean */
        double dev = 0.0;
        for (int j = 0; j < feat_len; j++) dev += fabs(fv[j] - global_mean[j]);
        dev /= feat_len;

        /* similarity with remote sensor (cross-partition) */
        int ri = s % share_n;
        double sim = cosine_sim(fv, recv_feats + (size_t)ri*feat_len, feat_len);

        local_scores[s] = ALPHA * dev + BETA * (1.0 - sim);
        if (local_scores[s] < sc_min) sc_min = local_scores[s];
        if (local_scores[s] > sc_max) sc_max = local_scores[s];
    }
    free(global_mean);
    free(recv_feats);
    free(local_feats);
    te = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║          STEP 7: GLOBAL AGGREGATION              ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  MPI_Allreduce used to compute TRUE global mean  ║\n");
        printf("║  across all ranks simultaneously                 ║\n");
        printf("║                                                  ║\n");
        printf("║  Score = %.1f*Deviation + %.1f*(1-CrossSimilarity) ║\n", ALPHA, BETA);
        printf("║  Deviation measured from GLOBAL mean (all nodes) ║\n");
        printf("║  Similarity measured against REMOTE sensors      ║\n");
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
     * STEP 8: RESULT COLLECTION (all -> master)
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
        printf("║          STEP 8: RESULT COLLECTION               ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  Method : MPI_Gatherv (all workers -> master)    ║\n");
        printf("║  Master collected %4d anomaly scores             ║\n", num_sensors);
        printf("║  Step Time: %-34.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    /* ═══════════════════════════════════════════════════
     * STEP 9: FINAL RANKING (master only)
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
        printf("║      STEP 9: FINAL RANKING  (Master Node)        ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  All %4d sensor scores sorted by anomaly score   ║\n", num_sensors);
        printf("║  Step Time: %-34.4f sec ║\n", te - ts);
        printf("╚══════════════════════════════════════════════════╝\n");

        printf("\n╔════════╦══════════════╦═══════════════════════════╗\n");
        printf("║      TOP %2d ANOMALOUS SENSORS  (Advanced)         ║\n", TOP_N);
        printf("╠════════╦══════════════╬═══════════════════════════╣\n");
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
        printf("  TOTAL Advanced Parallel Time (%d ranks): %.4f sec\n",
               size, t_end - t_start);
        printf("====================================================\n\n");
    }

    MPI_Finalize();
    return 0;
}

/*
 * Name       : Aleena Zahra
 * Student ID : 23i-2514
 * Assignment : 3 - Distributed Sensor Intelligent System
 * File       : Sequential_version.c
 *
 * Description:
 *   Multi-stage sequential sensor intelligence pipeline:
 *   1. Dataset Loading
 *   2. Sliding Window Feature Extraction (mean, variance, energy, magnitude)
 *   3. Feature Vector Construction
 *   4. Cosine Similarity Computation (K random pairs)
 *   5. Anomaly Scoring (deviation + similarity)
 *   6. Top-10 Anomalous Sensor Ranking
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* ─────────────────────── tuneable constants ─────────────────────── */
#define WINDOW_SIZE     20      /* sliding window length              */
#define K_PAIRS         500     /* random sensor pairs for similarity */
#define ALPHA           0.6     /* weight for deviation term          */
#define BETA            0.4     /* weight for similarity term         */
#define TOP_N           10      /* anomalous sensors to display       */
#define FEATURES_PER_WIN 4      /* mean, var, energy, magnitude       */
/* ──────────────────────────────────────────────────────────────────── */

/* ──────────── data structures ──────────── */
typedef struct {
    int    sensor_id;
    double score;
} SensorScore;

/* ──────────── globals ──────────── */
static int     num_sensors  = 0;
static int     num_timesteps = 0;
static double **sensor_data  = NULL;   /* [sensor][timestep]         */
static int     feat_len      = 0;      /* features per sensor vector  */
static double **feat_vectors = NULL;   /* [sensor][feat_len]          */
static double  *global_mean  = NULL;   /* mean of each feature dim    */
static double  *anomaly_scores = NULL;

/* ──────────── helpers ──────────── */
static double vec_dot(const double *a, const double *b, int n) {
    double s = 0.0;
    for (int i = 0; i < n; i++) s += a[i] * b[i];
    return s;
}
static double vec_norm(const double *a, int n) {
    return sqrt(vec_dot(a, a, n));
}
static double cosine_similarity(const double *a, const double *b, int n) {
    double na = vec_norm(a, n);
    double nb = vec_norm(b, n);
    if (na < 1e-12 || nb < 1e-12) return 0.0;
    return vec_dot(a, b, n) / (na * nb);
}

/* ──────────── Step 1: Dataset Loading ──────────── */
static int load_dataset(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("fopen"); return -1; }

    char line[256];
    /* skip header */
    if (!fgets(line, sizeof(line), fp)) { fclose(fp); return -1; }

    /* first pass: find dimensions */
    int max_s = -1, max_t = -1;
    while (fgets(line, sizeof(line), fp)) {
        int s, t; float v;
        if (sscanf(line, "%d,%d,%f", &s, &t, &v) == 3) {
            if (s > max_s) max_s = s;
            if (t > max_t) max_t = t;
        }
    }
    num_sensors   = max_s + 1;
    num_timesteps = max_t + 1;

    /* allocate */
    sensor_data = (double **)malloc(num_sensors * sizeof(double *));
    for (int i = 0; i < num_sensors; i++) {
        sensor_data[i] = (double *)calloc(num_timesteps, sizeof(double));
    }

    /* second pass: fill */
    rewind(fp);
    fgets(line, sizeof(line), fp); /* skip header again */
    while (fgets(line, sizeof(line), fp)) {
        int s, t; float v;
        if (sscanf(line, "%d,%d,%f", &s, &t, &v) == 3) {
            sensor_data[s][t] = (double)v;
        }
    }
    fclose(fp);

    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║           STEP 1: DATASET LOADING                ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  File        : %-33s ║\n", filename);
    printf("║  Sensors     : %-33d ║\n", num_sensors);
    printf("║  Timesteps   : %-33d ║\n", num_timesteps);
    printf("║  Total Rows  : %-33d ║\n", num_sensors * num_timesteps);
    printf("║  Memory Used : %-30.2f MB ║\n",
           (double)num_sensors * num_timesteps * sizeof(double) / (1024*1024));
    printf("║                                                  ║\n");
    printf("║  Sample data (first 5 readings of sensor 0):    ║\n");
    for (int t = 0; t < 5 && t < num_timesteps; t++)
        printf("║    Sensor 0 | Timestep %3d | Value: %8.2f      ║\n",
               t, sensor_data[0][t]);
    printf("╚══════════════════════════════════════════════════╝\n");

    return 0;
}

/* ──────────── Step 2 & 3: Feature Extraction + Vector Construction ──────────── */
static void extract_features(void) {
    int num_windows = num_timesteps / WINDOW_SIZE;
    feat_len = num_windows * FEATURES_PER_WIN;

    feat_vectors = (double **)malloc(num_sensors * sizeof(double *));
    for (int s = 0; s < num_sensors; s++) {
        feat_vectors[s] = (double *)malloc(feat_len * sizeof(double));
        for (int w = 0; w < num_windows; w++) {
            int base = w * WINDOW_SIZE;
            double mean = 0.0, var = 0.0, energy = 0.0;

            for (int i = 0; i < WINDOW_SIZE; i++)
                mean += sensor_data[s][base + i];
            mean /= WINDOW_SIZE;

            for (int i = 0; i < WINDOW_SIZE; i++) {
                double x = sensor_data[s][base + i];
                var    += (x - mean) * (x - mean);
                energy += x * x;
            }
            var /= WINDOW_SIZE;
            double magnitude = sqrt(energy);

            int fi = w * FEATURES_PER_WIN;
            feat_vectors[s][fi + 0] = mean;
            feat_vectors[s][fi + 1] = var;
            feat_vectors[s][fi + 2] = energy;
            feat_vectors[s][fi + 3] = magnitude;
        }
    }

    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║     STEP 2: SLIDING WINDOW FEATURE EXTRACTION    ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  Window Size     : %-29d ║\n", WINDOW_SIZE);
    printf("║  Windows/Sensor  : %-29d ║\n", num_windows);
    printf("║  Features/Window : %-29d ║\n", FEATURES_PER_WIN);
    printf("║  Features Computed: Mean, Variance, Energy, Mag  ║\n");
    printf("║                                                  ║\n");
    printf("║  Sample — Sensor 0, Window 0:                    ║\n");
    printf("║    Mean      = %10.4f                        ║\n", feat_vectors[0][0]);
    printf("║    Variance  = %10.4f                        ║\n", feat_vectors[0][1]);
    printf("║    Energy    = %10.4f                        ║\n", feat_vectors[0][2]);
    printf("║    Magnitude = %10.4f                        ║\n", feat_vectors[0][3]);
    printf("╚══════════════════════════════════════════════════╝\n");

    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║       STEP 3: FEATURE VECTOR CONSTRUCTION        ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  Total sensors         : %-23d ║\n", num_sensors);
    printf("║  Feature vector length : %-23d ║\n", feat_len);
    printf("║  Format per sensor:                              ║\n");
    printf("║  [mean1,var1,energy1,mag1, mean2,var2,...]       ║\n");
    printf("║                                                  ║\n");
    printf("║  Sample — Sensor 0 feature vector (first 8):    ║\n");
    printf("║  ");
    for (int j = 0; j < 8 && j < feat_len; j++)
        printf("%7.2f ", feat_vectors[0][j]);
    printf("║\n");
    printf("╚══════════════════════════════════════════════════╝\n");
}

/* ──────────── Step 4: Similarity Computation (K random pairs) ──────────── */
static void compute_similarity_pairs(void) {
    srand(42);
    double total = 0.0;
    double min_sim = 1.0, max_sim = 0.0;

    /* store a few sample pairs to display */
    int   sample_a[5], sample_b[5];
    double sample_sim[5];
    int   stored = 0;

    for (int k = 0; k < K_PAIRS; k++) {
        int a = rand() % num_sensors;
        int b = rand() % num_sensors;
        if (a == b) b = (b + 1) % num_sensors;
        double sim = cosine_similarity(feat_vectors[a], feat_vectors[b], feat_len);
        total += sim;
        if (sim < min_sim) min_sim = sim;
        if (sim > max_sim) max_sim = sim;
        if (stored < 5) {
            sample_a[stored] = a; sample_b[stored] = b;
            sample_sim[stored] = sim; stored++;
        }
    }

    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║         STEP 4: COSINE SIMILARITY COMPUTATION    ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  Random pairs evaluated : %-22d ║\n", K_PAIRS);
    printf("║  Average similarity     : %-22.4f ║\n", total / K_PAIRS);
    printf("║  Min similarity         : %-22.4f ║\n", min_sim);
    printf("║  Max similarity         : %-22.4f ║\n", max_sim);
    printf("║                                                  ║\n");
    printf("║  Sample pair results:                            ║\n");
    printf("║  %-6s  %-6s  %-10s                      ║\n","Sensor A","Sensor B","Similarity");
    printf("║  %-6s  %-6s  %-10s                      ║\n","--------","--------","----------");
    for (int i = 0; i < stored; i++)
        printf("║  %-8d  %-8d  %-10.4f                    ║\n",
               sample_a[i], sample_b[i], sample_sim[i]);
    printf("╚══════════════════════════════════════════════════╝\n");
}

/* ──────────── Step 5: Anomaly Scoring ──────────── */
static void compute_anomaly_scores(void) {
    /* compute global mean feature vector (μ_F) */
    global_mean = (double *)calloc(feat_len, sizeof(double));
    for (int s = 0; s < num_sensors; s++)
        for (int j = 0; j < feat_len; j++)
            global_mean[j] += feat_vectors[s][j];
    for (int j = 0; j < feat_len; j++)
        global_mean[j] /= num_sensors;

    anomaly_scores = (double *)malloc(num_sensors * sizeof(double));

    double min_dev = 1e18, max_dev = 0.0;
    double min_score = 1e18, max_score = 0.0;

    for (int s = 0; s < num_sensors; s++) {
        double deviation = 0.0;
        for (int j = 0; j < feat_len; j++)
            deviation += fabs(feat_vectors[s][j] - global_mean[j]);
        deviation /= feat_len;

        int neighbor = (s + 1) % num_sensors;
        double sim = cosine_similarity(feat_vectors[s], feat_vectors[neighbor], feat_len);

        anomaly_scores[s] = ALPHA * deviation + BETA * (1.0 - sim);

        if (deviation < min_dev) min_dev = deviation;
        if (deviation > max_dev) max_dev = deviation;
        if (anomaly_scores[s] < min_score) min_score = anomaly_scores[s];
        if (anomaly_scores[s] > max_score) max_score = anomaly_scores[s];
    }

    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║            STEP 5: ANOMALY SCORING               ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  Formula:                                        ║\n");
    printf("║  Score = alpha*Deviation + beta*(1-Similarity)   ║\n");
    printf("║  Alpha (deviation weight) : %-20.2f ║\n", ALPHA);
    printf("║  Beta  (similarity weight): %-20.2f ║\n", BETA);
    printf("║                                                  ║\n");
    printf("║  Deviation range : [%9.4f  to %9.4f]    ║\n", min_dev, max_dev);
    printf("║  Score range     : [%9.4f  to %9.4f]    ║\n", min_score, max_score);
    printf("║                                                  ║\n");
    printf("║  Sample scores (first 5 sensors):                ║\n");
    printf("║  %-8s  %-12s                          ║\n", "Sensor", "Score");
    printf("║  %-8s  %-12s                          ║\n", "------", "------------");
    for (int s = 0; s < 5 && s < num_sensors; s++)
        printf("║  %-8d  %-12.4f                          ║\n", s, anomaly_scores[s]);
    printf("╚══════════════════════════════════════════════════╝\n");
}

/* ──────────── Step 6: Ranking – Top 10 ──────────── */
static int cmp_scores(const void *a, const void *b) {
    const SensorScore *sa = (const SensorScore *)a;
    const SensorScore *sb = (const SensorScore *)b;
    return (sb->score > sa->score) - (sb->score < sa->score);
}

static void rank_and_display(void) {
    SensorScore *ranked = (SensorScore *)malloc(num_sensors * sizeof(SensorScore));
    for (int s = 0; s < num_sensors; s++) {
        ranked[s].sensor_id = s;
        ranked[s].score     = anomaly_scores[s];
    }
    qsort(ranked, num_sensors, sizeof(SensorScore), cmp_scores);

    printf("\n╔══════════════════════════════════════════╗\n");
    printf("║        TOP %2d ANOMALOUS SENSORS           ║\n", TOP_N);
    printf("╠═══════════╦══════════════════════════════╣\n");
    printf("║   Rank    ║  Sensor ID  │  Anomaly Score ║\n");
    printf("╠═══════════╬══════════════════════════════╣\n");
    for (int i = 0; i < TOP_N && i < num_sensors; i++) {
        printf("║    %3d    ║   %6d    │   %12.6f  ║\n",
               i + 1, ranked[i].sensor_id, ranked[i].score);
    }
    printf("╚═══════════╩══════════════════════════════╝\n\n");
    free(ranked);
}

/* ──────────── main ──────────── */
int main(int argc, char *argv[]) {
    const char *fname = (argc > 1) ? argv[1] : "Dataset.csv";

    struct timespec t0, t1, ts, te;
    double step_time;

    printf("\n");
    printf("====================================================\n");
    printf("   SEQUENTIAL SENSOR INTELLIGENCE PIPELINE\n");
    printf("   Assignment 3 — Distributed Sensor System\n");
    printf("====================================================\n");

    clock_gettime(CLOCK_MONOTONIC, &t0);

    /* ── Step 1: Dataset Loading ── */
    clock_gettime(CLOCK_MONOTONIC, &ts);
    if (load_dataset(fname) != 0) {
        fprintf(stderr, "Failed to load dataset.\n");
        return 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &te);
    step_time = (te.tv_sec - ts.tv_sec) + (te.tv_nsec - ts.tv_nsec) / 1e9;
    printf("  >> Step 1 completed in %.4f seconds\n", step_time);

    /* ── Steps 2 & 3: Feature Extraction & Vector Construction ── */
    clock_gettime(CLOCK_MONOTONIC, &ts);
    extract_features();
    clock_gettime(CLOCK_MONOTONIC, &te);
    step_time = (te.tv_sec - ts.tv_sec) + (te.tv_nsec - ts.tv_nsec) / 1e9;
    printf("  >> Steps 2 & 3 completed in %.4f seconds\n", step_time);

    /* ── Step 4: Similarity Computation ── */
    clock_gettime(CLOCK_MONOTONIC, &ts);
    compute_similarity_pairs();
    clock_gettime(CLOCK_MONOTONIC, &te);
    step_time = (te.tv_sec - ts.tv_sec) + (te.tv_nsec - ts.tv_nsec) / 1e9;
    printf("  >> Step 4 completed in %.4f seconds\n", step_time);

    /* ── Step 5: Anomaly Scoring ── */
    clock_gettime(CLOCK_MONOTONIC, &ts);
    compute_anomaly_scores();
    clock_gettime(CLOCK_MONOTONIC, &te);
    step_time = (te.tv_sec - ts.tv_sec) + (te.tv_nsec - ts.tv_nsec) / 1e9;
    printf("  >> Step 5 completed in %.4f seconds\n", step_time);

    /* ── Step 6: Ranking ── */
    clock_gettime(CLOCK_MONOTONIC, &ts);
    rank_and_display();
    clock_gettime(CLOCK_MONOTONIC, &te);
    step_time = (te.tv_sec - ts.tv_sec) + (te.tv_nsec - ts.tv_nsec) / 1e9;
    printf("  >> Step 6 completed in %.4f seconds\n", step_time);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    double elapsed = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;

    printf("\n====================================================\n");
    printf("  TOTAL Sequential Execution Time: %.4f seconds\n", elapsed);
    printf("====================================================\n\n");

    /* cleanup */
    for (int s = 0; s < num_sensors; s++) {
        free(sensor_data[s]);
        free(feat_vectors[s]);
    }
    free(sensor_data);
    free(feat_vectors);
    free(global_mean);
    free(anomaly_scores);
    return 0;
}
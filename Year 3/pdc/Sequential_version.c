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

/* tuneable constants */
#define WINDOW_SIZE     20      /* sliding window length              */
#define K_PAIRS         500     /* random sensor pairs for similarity */
#define ALPHA           0.6     /* weight for deviation term          */
#define BETA            0.4     /* weight for similarity term         */
#define TOP_N           10      /* anomalous sensors to display       */
#define FEATURES_PER_WIN 4      /* mean, var, energy, magnitude       */


/*  data structures  */
typedef struct {
    int    sensor_id;
    double score;
} SensorScore;

/*  globals  */
static int     num_sensors  = 0;
static int     num_timesteps = 0;
static double **sensor_data  = NULL;   /* [sensor][timestep]         */
static int     feat_len      = 0;      /* features per sensor vector  */
static double **feat_vectors = NULL;   /* [sensor][feat_len]          */
static double  *global_mean  = NULL;   /* mean of each feature dim    */
static double  *anomaly_scores = NULL;

/*  helpers  */
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

/*  Step 1: Dataset Loading  */
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
    printf("[Load] Sensors: %d  |  Timesteps: %d\n", num_sensors, num_timesteps);

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
    return 0;
}

/*  Step 2 & 3: Feature Extraction + Vector Construction  */
static void extract_features(void) {
    int num_windows = num_timesteps / WINDOW_SIZE;
    feat_len = num_windows * FEATURES_PER_WIN;

    feat_vectors = (double **)malloc(num_sensors * sizeof(double *));
    for (int s = 0; s < num_sensors; s++) {
        feat_vectors[s] = (double *)malloc(feat_len * sizeof(double));
        for (int w = 0; w < num_windows; w++) {
            int base = w * WINDOW_SIZE;
            double mean = 0.0, var = 0.0, energy = 0.0;

            /* mean */
            for (int i = 0; i < WINDOW_SIZE; i++)
                mean += sensor_data[s][base + i];
            mean /= WINDOW_SIZE;

            /* variance, energy */
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
    printf("[Feature] Extraction complete. Vector length per sensor: %d\n", feat_len);
}

/*  Step 4: Similarity Computation (K random pairs)  */
static void compute_similarity_pairs(void) {
    printf("[Similarity] Computing cosine similarity for %d random pairs...\n", K_PAIRS);
    srand(42);
    double total = 0.0;
    for (int k = 0; k < K_PAIRS; k++) {
        int a = rand() % num_sensors;
        int b = rand() % num_sensors;
        if (a == b) b = (b + 1) % num_sensors;
        double sim = cosine_similarity(feat_vectors[a], feat_vectors[b], feat_len);
        total += sim;
    }
    printf("[Similarity] Average pairwise similarity: %.4f\n", total / K_PAIRS);
}

/*  Step 5: Anomaly Scoring  */
static void compute_anomaly_scores(void) {
    /* compute global mean feature vector (μ_F) */
    global_mean = (double *)calloc(feat_len, sizeof(double));
    for (int s = 0; s < num_sensors; s++)
        for (int j = 0; j < feat_len; j++)
            global_mean[j] += feat_vectors[s][j];
    for (int j = 0; j < feat_len; j++)
        global_mean[j] /= num_sensors;

    anomaly_scores = (double *)malloc(num_sensors * sizeof(double));

    for (int s = 0; s < num_sensors; s++) {
        /* Deviation from global feature behavior */
        double deviation = 0.0;
        for (int j = 0; j < feat_len; j++)
            deviation += fabs(feat_vectors[s][j] - global_mean[j]);
        deviation /= feat_len;

        /* Similarity with neighbouring sensor */
        int neighbor = (s + 1) % num_sensors;
        double sim = cosine_similarity(feat_vectors[s], feat_vectors[neighbor], feat_len);

        /* Final anomaly score */
        anomaly_scores[s] = ALPHA * deviation + BETA * (1.0 - sim);
    }
    printf("[Anomaly] Scoring complete.\n");
}

/*  Step 6: Ranking – Top 10  */
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

/*  main  */
int main(int argc, char *argv[]) {
    const char *fname = (argc > 1) ? argv[1] : "Dataset.csv";

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    printf("=== Sequential Sensor Intelligence Pipeline ===\n\n");

    /* Step 1 */
    if (load_dataset(fname) != 0) {
        fprintf(stderr, "Failed to load dataset.\n");
        return 1;
    }

    /* Steps 2 & 3 */
    extract_features();

    /* Step 4 */
    compute_similarity_pairs();

    /* Step 5 */
    compute_anomaly_scores();

    /* Step 6 */
    rank_and_display();

    clock_gettime(CLOCK_MONOTONIC, &t1);
    double elapsed = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
    printf("[Timing] Sequential execution time: %.4f seconds\n", elapsed);

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

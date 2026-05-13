// aleena zahra 23i2514 ds b assignment 2
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
using namespace chrono;

// Stop-words removal
static const unordered_set<string> STOPWORDS = {
    "the","is","at","which","on","and","a","an","to","of",
    "in","it","this","that","with","for","as","are","was","be"
};

bool isStopWord(const string& w) {
    return STOPWORDS.count(w) > 0;
}

// Tokenise one review 
vector<string> tokenize(const string& line) {
    vector<string> tokens;
    stringstream ss(line);
    string w;
    while (ss >> w) {
        transform(w.begin(), w.end(), w.begin(), ::tolower);
        if (!isStopWord(w) && !w.empty())
            tokens.push_back(w);
    }
    return tokens;
}

// Cosine similarity (TF-IDF maps)
double cosine(const map<string,double>& a, const map<string,double>& b) {
    double dot = 0, na = 0, nb = 0;
    for (auto& p : a) {
        na += p.second * p.second;
        auto it = b.find(p.first);
        if (it != b.end()) dot += p.second * it->second;
    }
    for (auto& p : b) nb += p.second * p.second;
    return dot / (sqrt(na) * sqrt(nb) + 1e-9);
}

int main() {
    // 0. Load dataset 
    auto t0 = high_resolution_clock::now();

    ifstream file("Dataset.csv");
    if (!file.is_open()) { cerr << "ERROR: Cannot open Dataset.csv\n"; return 1; }
    vector<string> docs;
    string line;
    while (getline(file, line))
        if (!line.empty()) docs.push_back(line);
    file.close();

    int N = (int)docs.size();

    int numThreads = omp_get_max_threads();
    cout << "OpenMP threads available: " << numThreads << "\n\n";

    // Parallel Tokenisation + Local Frequency
    vector<map<string,int>> docTF_raw(N);
    vector<vector<string>>  docTokens(N);

    // Thread-local frequency maps, merged after the parallel section
    vector<map<string,int>> localFreq(numThreads);

    #pragma omp parallel num_threads(numThreads)
    {
        int tid = omp_get_thread_num();
        map<string,int>& myFreq = localFreq[tid];

        #pragma omp for schedule(dynamic, 256)
        for (int i = 0; i < N; i++) {
            docTokens[i] = tokenize(docs[i]);
            for (auto& w : docTokens[i]) {
                myFreq[w]++;
                docTF_raw[i][w]++;   
            }
        }
    }

    // Serial merge of thread-local maps
    map<string,int> globalFreq;
    for (int t = 0; t < numThreads; t++)
        for (auto& p : localFreq[t])
            globalFreq[p.first] += p.second;

    // Vocabulary 
    vector<string> vocab;
    for (auto& p : globalFreq) vocab.push_back(p.first);
    int V = (int)vocab.size();
    unordered_map<string,int> wordIdx;
    for (int i = 0; i < V; i++) wordIdx[vocab[i]] = i;
    cout << "Vocabulary size: " << V << "\n\n";

    // Word Frequency n Top 10  
    vector<pair<string,int>> freqVec(globalFreq.begin(), globalFreq.end());
    sort(freqVec.begin(), freqVec.end(),
         [](const pair<string,int>& a, const pair<string,int>& b){
             return a.second > b.second; });

    cout << "Top 10 most frequent words:\n";
    for (int i = 0; i < 10 && i < (int)freqVec.size(); i++)
        cout << "  " << freqVec[i].first << " : " << freqVec[i].second << "\n";
    cout << "\n";

    // TF-IDF parallel DF computation 
    vector<map<string,int>> localDF(numThreads);

    #pragma omp parallel num_threads(numThreads)
    {
        int tid = omp_get_thread_num();
        #pragma omp for schedule(dynamic, 256)
        for (int i = 0; i < N; i++)
            for (auto& p : docTF_raw[i])
                localDF[tid][p.first]++;
    }
    map<string,int> df_map;
    for (int t = 0; t < numThreads; t++)
        for (auto& p : localDF[t])
            df_map[p.first] += p.second;

    // IDF 
    map<string,double> idf;
    for (auto& p : df_map)
        idf[p.first] = log((double)N / (p.second + 1.0));

    // Build TF-IDF per doc in parallel
    vector<map<string,double>> tfidf(N);
    #pragma omp parallel for schedule(dynamic, 256) num_threads(numThreads)
    for (int i = 0; i < N; i++) {
        int docLen = (int)docTokens[i].size();
        if (docLen == 0) continue;
        for (auto& p : docTF_raw[i]) {
            double tf = (double)p.second / docLen;
            tfidf[i][p.first] = tf * idf.at(p.first);
        }
    }
    cout << "TF-IDF computed for all documents.\n\n";

    // K-Means Clustering (K = 5) 
    const int K     = 5;
    const int ITERS = 10;
    const int FEAT  = min(100, V);

    vector<string> featWords;
    for (int i = 0; i < FEAT; i++) featWords.push_back(freqVec[i].first);
    unordered_map<string,int> featIdx;
    for (int i = 0; i < FEAT; i++) featIdx[featWords[i]] = i;

    // Feature matrix – built in parallel
    vector<vector<double>> X(N, vector<double>(FEAT, 0.0));
    #pragma omp parallel for schedule(dynamic, 256) num_threads(numThreads)
    for (int i = 0; i < N; i++)
        for (auto& p : tfidf[i]) {
            auto it = featIdx.find(p.first);
            if (it != featIdx.end())
                X[i][it->second] = p.second;
        }

    // Init centroids
    vector<vector<double>> centroids(K, vector<double>(FEAT, 0.0));
    for (int k = 0; k < K; k++) centroids[k] = X[k];
    vector<int> cluster(N, 0);

    for (int iter = 0; iter < ITERS; iter++) {
        // Parallel assignment 
        #pragma omp parallel for schedule(dynamic, 256) num_threads(numThreads)
        for (int i = 0; i < N; i++) {
            double bestDist = 1e18;
            int    best     = 0;
            for (int k = 0; k < K; k++) {
                double dist = 0;
                for (int f = 0; f < FEAT; f++) {
                    double d = X[i][f] - centroids[k][f];
                    dist += d * d;
                }
                if (dist < bestDist) { bestDist = dist; best = k; }
            }
            cluster[i] = best;   
        }

        // Parallel centroid recomputation 
        int T = numThreads;
        vector<vector<vector<double>>> localSum(T, vector<vector<double>>(K, vector<double>(FEAT, 0.0)));
        vector<vector<int>>           localCnt(T, vector<int>(K, 0));

        #pragma omp parallel num_threads(T)
        {
            int tid = omp_get_thread_num();
            #pragma omp for schedule(dynamic, 256)
            for (int i = 0; i < N; i++) {
                int k = cluster[i];
                localCnt[tid][k]++;
                for (int f = 0; f < FEAT; f++)
                    localSum[tid][k][f] += X[i][f];
            }
        }
        // Merge
        vector<vector<double>> newC(K, vector<double>(FEAT, 0.0));
        vector<int> cnt(K, 0);
        for (int t = 0; t < T; t++)
            for (int k = 0; k < K; k++) {
                cnt[k] += localCnt[t][k];
                for (int f = 0; f < FEAT; f++)
                    newC[k][f] += localSum[t][k][f];
            }
        for (int k = 0; k < K; k++)
            if (cnt[k] > 0)
                for (int f = 0; f < FEAT; f++)
                    centroids[k][f] = newC[k][f] / cnt[k];
    }

    vector<int> clusterCount(K, 0);
    for (int c : cluster) clusterCount[c]++;
    cout << "K-Means Clusters (K=" << K << ", " << ITERS << " iterations):\n";
    for (int i = 0; i < K; i++)
        cout << "  Cluster " << i+1 << " -> " << clusterCount[i] << " documents\n";
    cout << "\n";

    // Parallel Cosine Similarity Search for 100 random pairs
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, N-1);
    vector<pair<int,int>> pairs(100);
    for (auto& p : pairs) p = {dist(rng), dist(rng)};

    vector<double> simScores(100, 0.0);
    #pragma omp parallel for schedule(dynamic, 4) num_threads(numThreads)
    for (int i = 0; i < 100; i++)
        simScores[i] = cosine(tfidf[pairs[i].first], tfidf[pairs[i].second]);

    double simSum = 0;
    cout << "Cosine Similarity (100 pairs) [sample of 10 shown]:\n";
    for (int i = 0; i < 100; i++) {
        simSum += simScores[i];
        if (i < 10)
            cout << "  Doc " << pairs[i].first << " & Doc " << pairs[i].second
                 << " => similarity = " << fixed << setprecision(4) << simScores[i] << "\n";
    }
    cout << "  (90 more pairs computed)\n";
    cout << "  Average similarity: " << fixed << setprecision(4) << simSum/100 << "\n\n";


    auto t1 = high_resolution_clock::now();
    double elapsed = duration<double>(t1 - t0).count();
    cout << "OpenMP Execution Time : " << fixed << setprecision(4)
         << elapsed << " seconds\n";
    cout << "Threads used          : " << numThreads << "\n";

    return 0;
}

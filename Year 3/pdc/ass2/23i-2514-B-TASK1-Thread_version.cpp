// aleena zahra 23i2514 ds b assignment 2
#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <barrier>        
using namespace std;
using namespace chrono;

class SpinBarrier {
    int          total;
    atomic<int>  waiting{0};
    atomic<int>  generation{0};
public:
    explicit SpinBarrier(int n) : total(n) {}
    void arrive_and_wait() {
        int gen = generation.load();
        if (++waiting == total) {
            waiting = 0;
            generation++;
        } else {
            while (generation.load() == gen)
                this_thread::yield();
        }
    }
};

//  Stop-words
static const unordered_set<string> STOPWORDS = {
    "the","is","at","which","on","and","a","an","to","of",
    "in","it","this","that","with","for","as","are","was","be"
};
bool isStopWord(const string& w) { return STOPWORDS.count(w) > 0; }

//  Tokenise
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

//  Cosine similarity
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

//  Shared state 
struct SharedState {
    // Input
    const vector<string>*          docs    = nullptr;
    int                            N       = 0;
    int                            T       = 0;   // thread count

    vector<vector<string>>*        docTokens = nullptr;
    vector<map<string,int>>*       docTF_raw = nullptr;
    vector<map<string,int>>*       localFreq = nullptr;
    map<string,int>*               globalFreq = nullptr;
    map<string,double>*            idf        = nullptr;
    vector<map<string,double>>*    tfidf      = nullptr;
    vector<vector<double>>*        X          = nullptr;
    int                            FEAT       = 0;
    int                            K          = 5;
    int                            ITERS      = 10;
    vector<vector<double>>*        centroids  = nullptr;
    vector<int>*                   cluster    = nullptr;
    vector<vector<vector<double>>>* localSum  = nullptr;
    vector<vector<int>>*            localCnt  = nullptr;
    vector<pair<int,int>>*         pairs      = nullptr;
    vector<double>*                simScores  = nullptr;
};

//  Phase 1 – Tokenisation + local frequency
void workerPhase1(int tid, int start, int end, SharedState& S) {
    auto& myFreq = (*S.localFreq)[tid];
    for (int i = start; i < end; i++) {
        (*S.docTokens)[i] = tokenize((*S.docs)[i]);
        for (auto& w : (*S.docTokens)[i]) {
            myFreq[w]++;
            (*S.docTF_raw)[i][w]++;   
        }
    }
}

//  Phase 2 – TF-IDF computation
void workerPhase2(int start, int end, SharedState& S) {
    for (int i = start; i < end; i++) {
        int docLen = (int)(*S.docTokens)[i].size();
        if (docLen == 0) continue;
        for (auto& p : (*S.docTF_raw)[i]) {
            double tf = (double)p.second / docLen;
            (*S.tfidf)[i][p.first] = tf * S.idf->at(p.first);
        }
    }
}

//  Phase 3a K-Means assignment
void workerKmeansAssign(int start, int end, SharedState& S) {
    int K    = S.K;
    int FEAT = S.FEAT;
    auto& C  = *S.centroids;
    auto& X  = *S.X;
    auto& cl = *S.cluster;

    for (int i = start; i < end; i++) {
        double bestDist = 1e18;
        int    best     = 0;
        for (int k = 0; k < K; k++) {
            double dist = 0;
            for (int f = 0; f < FEAT; f++) {
                double d = X[i][f] - C[k][f];
                dist += d * d;
            }
            if (dist < bestDist) { bestDist = dist; best = k; }
        }
        cl[i] = best;
    }
}

//  Phase 3b – K-Means centroid accumulation
void workerKmeansAccum(int tid, int start, int end, SharedState& S) {
    int K    = S.K;
    int FEAT = S.FEAT;
    auto& mySum = (*S.localSum)[tid];
    auto& myCnt = (*S.localCnt)[tid];

    for (int k = 0; k < K; k++) { fill(mySum[k].begin(), mySum[k].end(), 0.0); myCnt[k] = 0; }
    for (int i = start; i < end; i++) {
        int k = (*S.cluster)[i];
        myCnt[k]++;
        for (int f = 0; f < FEAT; f++)
            mySum[k][f] += (*S.X)[i][f];
    }
}

//  Feature matrix build
void workerBuildX(int start, int end, SharedState& S,
                  const unordered_map<string,int>& featIdx) {
    for (int i = start; i < end; i++)
        for (auto& p : (*S.tfidf)[i]) {
            auto it = featIdx.find(p.first);
            if (it != featIdx.end())
                (*S.X)[i][it->second] = p.second;
        }
}

//  Similarity search
void workerSimilarity(int start, int end, SharedState& S) {
    for (int i = start; i < end; i++) {
        int a = (*S.pairs)[i].first;
        int b = (*S.pairs)[i].second;
        (*S.simScores)[i] = cosine((*S.tfidf)[a], (*S.tfidf)[b]);
    }
}

//   partition work evenly among T threads
pair<int,int> getRange(int tid, int T, int N) {
    int chunk = N / T;
    int rem   = N % T;
    int start = tid * chunk + min(tid, rem);
    int end   = start + chunk + (tid < rem ? 1 : 0);
    return {start, end};
}

//  main
int main() {
    auto t0 = high_resolution_clock::now();

    // Load dataset
    ifstream file("Dataset.csv");
    if (!file.is_open()) { cerr << "ERROR: Cannot open Dataset.csv\n"; return 1; }
    vector<string> docs;
    string line;
    while (getline(file, line))
        if (!line.empty()) docs.push_back(line);
    file.close();

    int N = (int)docs.size();
    int T = min((int)thread::hardware_concurrency(), 8);
    if (T < 1) T = 4;
    cout << "Threads: " << T << "\n\n";

    // Allocate shared state
    SharedState S;
    S.docs      = &docs;
    S.N         = N;
    S.T         = T;

    vector<vector<string>>     docTokens(N);
    vector<map<string,int>>    docTF_raw(N);
    vector<map<string,int>>    localFreq(T);
    map<string,int>            globalFreq;
    map<string,double>         idf;
    vector<map<string,double>> tfidf(N);

    S.docTokens = &docTokens;
    S.docTF_raw = &docTF_raw;
    S.localFreq = &localFreq;
    S.globalFreq= &globalFreq;
    S.idf       = &idf;
    S.tfidf     = &tfidf;

    //  Phase 1: Parallel Tokenisation + local frequency
    {
        vector<thread> threads;
        for (int tid = 0; tid < T; tid++) {
            auto [s, e] = getRange(tid, T, N);
            threads.emplace_back(workerPhase1, tid, s, e, ref(S));
        }
        for (auto& th : threads) th.join();
    }

    // Serial merge of thread-local frequency maps
    for (int t = 0; t < T; t++)
        for (auto& p : localFreq[t])
            globalFreq[p.first] += p.second;

    // Vocabulary 
    vector<string> vocab;
    for (auto& p : globalFreq) vocab.push_back(p.first);
    int V = (int)vocab.size();
    cout << "Vocabulary size: " << V << "\n\n";

    //  Top 10 
    vector<pair<string,int>> freqVec(globalFreq.begin(), globalFreq.end());
    sort(freqVec.begin(), freqVec.end(),
         [](const pair<string,int>& a, const pair<string,int>& b){
             return a.second > b.second; });

    cout << "Top 10 most frequent words:\n";
    for (int i = 0; i < 10 && i < (int)freqVec.size(); i++)
        cout << "  " << freqVec[i].first << " : " << freqVec[i].second << "\n";
    cout << "\n";

    //  Document Frequency serial bc map traversal is fast
    map<string,int> df_map;
    for (int t = 0; t < T; t++) {
    }
    for (int i = 0; i < N; i++)
        for (auto& p : docTF_raw[i])
            df_map[p.first]++;    

    for (auto& p : df_map)
        idf[p.first] = log((double)N / (p.second + 1.0));

    //  Phase 2: Parallel TF-IDF
    {
        vector<thread> threads;
        for (int tid = 0; tid < T; tid++) {
            auto [s, e] = getRange(tid, T, N);
            threads.emplace_back(workerPhase2, s, e, ref(S));
        }
        for (auto& th : threads) th.join();
    }
    cout << "TF-IDF computed for all documents.\n\n";

    //  Phase 3: K-Means (K=5)
    const int K     = 5;
    const int ITERS = 10;
    const int FEAT  = min(100, V);

    vector<string> featWords;
    for (int i = 0; i < FEAT; i++) featWords.push_back(freqVec[i].first);
    unordered_map<string,int> featIdx;
    for (int i = 0; i < FEAT; i++) featIdx[featWords[i]] = i;

    // Feature matrix
    vector<vector<double>> X(N, vector<double>(FEAT, 0.0));
    S.X    = &X;
    S.FEAT = FEAT;
    S.K    = K;
    S.ITERS= ITERS;

    {
        vector<thread> threads;
        for (int tid = 0; tid < T; tid++) {
            auto [s, e] = getRange(tid, T, N);
            threads.emplace_back(workerBuildX, s, e, ref(S), cref(featIdx));
        }
        for (auto& th : threads) th.join();
    }

    // Centroids
    vector<vector<double>> centroids(K, vector<double>(FEAT, 0.0));
    for (int k = 0; k < K; k++) centroids[k] = X[k];
    vector<int> cluster(N, 0);
    S.centroids = &centroids;
    S.cluster   = &cluster;
    vector<vector<vector<double>>> localSum(T, vector<vector<double>>(K, vector<double>(FEAT, 0.0)));
    vector<vector<int>>            localCnt(T, vector<int>(K, 0));
    S.localSum = &localSum;
    S.localCnt = &localCnt;

    for (int iter = 0; iter < ITERS; iter++) {
        {
            vector<thread> threads;
            for (int tid = 0; tid < T; tid++) {
                auto [s, e] = getRange(tid, T, N);
                threads.emplace_back(workerKmeansAssign, s, e, ref(S));
            }
            for (auto& th : threads) th.join();
        }
        // Centroid accumulation in parallel
        {
            vector<thread> threads;
            for (int tid = 0; tid < T; tid++) {
                auto [s, e] = getRange(tid, T, N);
                threads.emplace_back(workerKmeansAccum, tid, s, e, ref(S));
            }
            for (auto& th : threads) th.join();
        }
        // Serial merge n update centroids
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

    //  Phase 4: Parallel Cosine Similarity for 100 pairs
    mt19937 rng(42);
    uniform_int_distribution<int> distrib(0, N-1);
    vector<pair<int,int>> pairs(100);
    for (auto& p : pairs) p = {distrib(rng), distrib(rng)};
    vector<double> simScores(100, 0.0);

    S.pairs     = &pairs;
    S.simScores = &simScores;

    {
        vector<thread> threads;
        for (int tid = 0; tid < T; tid++) {
            auto [s, e] = getRange(tid, T, 100);
            threads.emplace_back(workerSimilarity, s, e, ref(S));
        }
        for (auto& th : threads) th.join();
    }

    double simSum = 0;
    cout << "Cosine Similarity (100 pairs) [sample of 10 shown]:\n";
    for (int i = 0; i < 100; i++) {
        simSum += simScores[i];
        if (i < 10)
            cout << "  Doc " << pairs[i].first << " & Doc " << pairs[i].second
                 << " => similarity = " << fixed  << simScores[i] << "\n";
    }
    cout << "   (90 more pairs computed)\n";
    cout << "  Average similarity: " << fixed  << simSum/100 << "\n\n";

    //  Timing 
    auto t1 = high_resolution_clock::now();
    double elapsed = duration<double>(t1 - t0).count();
    cout << "Thread Execution Time : " << fixed 
         << elapsed << " seconds\n";
    cout << "Threads used          : " << T << "\n";

    return 0;
}

// aleena zahra 23i2514 ds-b assignment 2
#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

//  Stop-words 
static const unordered_set<string> STOPWORDS = {
    "the","is","at","which","on","and","a","an","to","of",
    "in","it","this","that","with","for","as","are","was","be"
};

bool isStopWord(const string& w) {
    return STOPWORDS.count(w) > 0;
}

//  Tokenise one review 
vector<string> tokenize(const string& line) {
    vector<string> tokens;
    stringstream ss(line);
    string w;
    while (ss >> w) {
        // lowercase
        transform(w.begin(), w.end(), w.begin(), ::tolower);
        if (!isStopWord(w) && !w.empty())
            tokens.push_back(w);
    }
    return tokens;
}

//  Cosine similarity between two TF maps 
double cosine(const map<string,double>& a, const map<string,double>& b) {
    double dot = 0, na = 0, nb = 0;
    for (auto& p : a) {
        na += p.second * p.second;
        auto it = b.find(p.first);
        if (it != b.end())
            dot += p.second * it->second;
    }
    for (auto& p : b) nb += p.second * p.second;
    return dot / (sqrt(na) * sqrt(nb) + 1e-9);
}

int main() {
    //  Load dataset 
    auto t0 = high_resolution_clock::now();

    ifstream file("Dataset.csv");
    if (!file.is_open()) {
        cerr << "ERROR: Cannot open Dataset.csv\n";
        return 1;
    }
    vector<string> docs;
    string line;
    while (getline(file, line))
        if (!line.empty()) docs.push_back(line);
    file.close();

    int N = (int)docs.size();

    //  Tokenisation + Stop-word Removal 
    vector<vector<string>>    docTokens(N);
    vector<map<string,int>>   docTF_raw(N);   
    map<string,int>           globalFreq;     

    for (int i = 0; i < N; i++) {
        docTokens[i] = tokenize(docs[i]);
        for (auto& w : docTokens[i]) {
            docTF_raw[i][w]++;
            globalFreq[w]++;
        }
    }

    //  Vocabulary 
    vector<string> vocab;
    for (auto& p : globalFreq) vocab.push_back(p.first);
    int V = (int)vocab.size();
    // map word → index for vector construction
    unordered_map<string,int> wordIdx;
    for (int i = 0; i < V; i++) wordIdx[vocab[i]] = i;

    cout << "Vocabulary size: " << V << "\n\n";

    //  Word Frequency – Top 10 
    vector<pair<string,int>> freqVec(globalFreq.begin(), globalFreq.end());
    sort(freqVec.begin(), freqVec.end(),
         [](const pair<string,int>& a, const pair<string,int>& b){
             return a.second > b.second; });

    cout << "Top 10 most frequent words:\n";
    for (int i = 0; i < 10 && i < (int)freqVec.size(); i++)
        cout << "  " << freqVec[i].first << " : " << freqVec[i].second << "\n";
    cout << "\n";

    //  TF-IDF Feature Extraction 
    //  IDF(t) = log( N / (df(t)+1) )   and i also did laplace smoothing
    //  TF(t,d) = count(t,d) / |d|

    // Document frequency per term
    map<string,int> df_map;
    for (int i = 0; i < N; i++)
        for (auto& p : docTF_raw[i])
            df_map[p.first]++;

    // IDF vector
    map<string,double> idf;
    for (auto& p : df_map)
        idf[p.first] = log((double)N / (p.second + 1.0));

    // TF-IDF per doc (sparse)
    vector<map<string,double>> tfidf(N);
    for (int i = 0; i < N; i++) {
        int docLen = (int)docTokens[i].size();
        if (docLen == 0) continue;
        for (auto& p : docTF_raw[i]) {
            double tf  = (double)p.second / docLen;
            tfidf[i][p.first] = tf * idf[p.first];
        }
    }
    cout << "TF-IDF computed for all documents.\n\n";

    //  K-Means Clustering (K = 5) 
    //  Feature: we represent each doc by a dense vector over
    //  the top-100 vocabulary terms (keeps it tractable).
    //  Distance = Euclidean on that feature vector.

    const int K       = 5;
    const int ITERS   = 10;
    const int FEAT    = min(100, V);   // top-FEAT vocab words as features

    // Build feature index from top-FEAT words
    vector<string> featWords;
    for (int i = 0; i < FEAT; i++) featWords.push_back(freqVec[i].first);
    unordered_map<string,int> featIdx;
    for (int i = 0; i < FEAT; i++) featIdx[featWords[i]] = i;

    // Build feature matrix
    vector<vector<double>> X(N, vector<double>(FEAT, 0.0));
    for (int i = 0; i < N; i++)
        for (auto& p : tfidf[i]) {
            auto it = featIdx.find(p.first);
            if (it != featIdx.end())
                X[i][it->second] = p.second;
        }

    // Initialise centroids = first K docs
    vector<vector<double>> centroids(K, vector<double>(FEAT, 0.0));
    for (int k = 0; k < K; k++) centroids[k] = X[k];

    vector<int> cluster(N, 0);

    for (int iter = 0; iter < ITERS; iter++) {
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
        // Recompute centroids
        vector<vector<double>> newC(K, vector<double>(FEAT, 0.0));
        vector<int> cnt(K, 0);
        for (int i = 0; i < N; i++) {
            int k = cluster[i];
            cnt[k]++;
            for (int f = 0; f < FEAT; f++)
                newC[k][f] += X[i][f];
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

    //  Cosine Similarity Search 100 random pairs
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, N-1);

    cout << "Cosine Similarity (100 random pairs) [sample of 10 shown]:\n";
    double simSum = 0;
    for (int i = 0; i < 100; i++) {
        int a = dist(rng), b = dist(rng);
        double sim = cosine(tfidf[a], tfidf[b]);
        simSum += sim;
        if (i < 10)
            cout << "  Doc " << a << " & Doc " << b
                 << " => similarity = " << fixed << setprecision(4) << sim << "\n";
    }
    cout << "   (90 more pairs computed)\n";
    cout << "  Average similarity: " << fixed << setprecision(4) << simSum/100 << "\n\n";

    
    auto t1 = high_resolution_clock::now();
    double elapsed = duration<double>(t1 - t0).count();
    cout << "Sequential Execution Time: " << fixed << setprecision(4)
         << elapsed << " seconds\n";

    return 0;
}

#include <iostream>
using namespace std;

class Graph {
    bool** adjacencyMat; 
    int size;           

    void allocateMemoryToMat(int size) {
        this->size = size;
        adjacencyMat = new bool*[size];
        for (int i = 0; i < size; i++) {
            adjacencyMat[i] = new bool[size];
            for (int j = 0; j < size; j++) {
                adjacencyMat[i][j] = false; 
            }
        }
    }

    void deallocateMemoryFromMat() {
        for (int i = 0; i < size; i++) {
            delete[] adjacencyMat[i];
        }
        delete[] adjacencyMat;
        adjacencyMat = NULL;
    }

    void copyMatrix(bool** mat, int oldSize) {
        for (int i = 0; i < oldSize; i++) {
            for (int j = 0; j < oldSize; j++) {
                adjacencyMat[i][j] = mat[i][j];
            }
        }
    }

public:
    Graph(int size) {
        this->size = 0;
        adjacencyMat = NULL;
        allocateMemoryToMat(size);
    }

    ~Graph() {
        deallocateMemoryFromMat();
    }

    void addEdge(int i, int j) {
        if (i < 0 || j < 0) {
            cout << "Invalid node id entered\n";
            return;
        }
        if (i >= size || j >= size) {
            addNode(max(i, j)); 
        }
        adjacencyMat[i][j] = true; // to make a directed graph
        adjacencyMat[j][i] = true; // to make an undirected graph
    }

    // Add a node to the graph
    void addNode(int i) {
        if (i >= size) {
            int newSize = i + 1; 
            bool** newMat = new bool*[newSize];
            for (int j = 0; j < newSize; j++) {
                newMat[j] = new bool[newSize];
                for (int k = 0; k < newSize; k++) {
                    newMat[j][k] = false; 
                }
            }

            copyMatrix(adjacencyMat, size);

            deallocateMemoryFromMat();
            adjacencyMat = newMat;
            size = newSize;
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << adjacencyMat[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph graph(2);
    graph.addNode(4);
    graph.addEdge(3, 4);
    graph.addEdge(1, 2);

    graph.print();

    return 0;
}

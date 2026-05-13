#include <iostream>
#include <climits> // For INT_MAX
using namespace std;

struct GraphNode {
    int id;
    GraphNode* next;
    GraphNode* nextNeighbour;
    int weight; // Added weight for edges

    GraphNode(int id) {
        this->id = id;
        this->nextNeighbour = NULL;
        this->next = NULL;
        this->weight = 0;
    }

    void addNeighbour(int neighbourId, int weight) {
        GraphNode* temp = nextNeighbour;
        while (temp != nullptr) {
            if (temp->id == neighbourId) return;
            temp = temp->nextNeighbour;
        }
        GraphNode* newNeighbour = new GraphNode(neighbourId);
        newNeighbour->weight = weight;
        newNeighbour->nextNeighbour = nextNeighbour;
        nextNeighbour = newNeighbour;
    }

    void printAdjacencyList() {
        cout << id << " -> ";
        GraphNode* temp = nextNeighbour;
        while (temp != NULL) {
            cout << temp->id << "(" << temp->weight << ") -> ";
            temp = temp->nextNeighbour;
        }
        cout << "NULL\n";
    }
};

class Graph {
    GraphNode* head;

public:
    Graph() {
        head = NULL;
    }

    void addNode(int id) {
        if (getNode(id) == NULL) {
            GraphNode* newNode = new GraphNode(id);
            newNode->next = head;
            head = newNode;
        }
    }

    GraphNode* getNode(int id) {
        GraphNode* temp = head;
        while (temp != NULL) {
            if (temp->id == id) {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void addEdge(int id1, int id2, int weight) {
        GraphNode* node1 = getNode(id1);
        if (node1 == nullptr) {
            addNode(id1);
            node1 = getNode(id1);
        }
        GraphNode* node2 = getNode(id2);
        if (node2 == nullptr) {
            addNode(id2);
            node2 = getNode(id2);
        }
        node1->addNeighbour(id2, weight);
    }

    void print() {
        GraphNode* temp = head;
        while (temp != NULL) {
            temp->printAdjacencyList();
            temp = temp->next;
        }
    }

    void dijkstra(int startId) {
        const int MAX_NODES = 100; // Fixed size for simplicity
        int distances[MAX_NODES];
        bool visited[MAX_NODES] = { false };
        for (int i = 0; i < MAX_NODES; i++) distances[i] = INT_MAX;

        distances[startId] = 0;

        for (int i = 0; i < MAX_NODES; i++) {
            int minDistance = INT_MAX, minNode = -1;

            for (int j = 0; j < MAX_NODES; j++) {
                if (!visited[j] && distances[j] < minDistance) {
                    minDistance = distances[j];
                    minNode = j;
                }
            }

            if (minNode == -1) break;
            visited[minNode] = true;

            GraphNode* currentNode = getNode(minNode);
            if (currentNode == NULL) continue;

            GraphNode* neighbour = currentNode->nextNeighbour;
            while (neighbour != NULL) {
                if (distances[minNode] + neighbour->weight < distances[neighbour->id]) {
                    distances[neighbour->id] = distances[minNode] + neighbour->weight;
                }
                neighbour = neighbour->nextNeighbour;
            }
        }

        cout << "Dijkstra's Shortest Paths:\n";
        for (int i = 0; i < MAX_NODES; i++) {
            if (distances[i] != INT_MAX) {
                cout << "Node " << i << ": " << distances[i] << "\n";
            }
        }
    }

    int heuristic(int nodeId, int targetId) {
        return abs(nodeId - targetId); // Simple heuristic for demonstration
    }

    void aStar(int startId, int targetId) {
        const int MAX_NODES = 100;
        int gScore[MAX_NODES], fScore[MAX_NODES];
        bool visited[MAX_NODES] = { false };

        for (int i = 0; i < MAX_NODES; i++) {
            gScore[i] = INT_MAX;
            fScore[i] = INT_MAX;
        }

        gScore[startId] = 0;
        fScore[startId] = heuristic(startId, targetId);

        while (true) {
            int minFScore = INT_MAX, currentNodeId = -1;

            for (int i = 0; i < MAX_NODES; i++) {
                if (!visited[i] && fScore[i] < minFScore) {
                    minFScore = fScore[i];
                    currentNodeId = i;
                }
            }

            if (currentNodeId == -1 || currentNodeId == targetId) break;
            visited[currentNodeId] = true;

            GraphNode* currentNode = getNode(currentNodeId);
            if (currentNode == NULL) continue;

            GraphNode* neighbour = currentNode->nextNeighbour;
            while (neighbour != NULL) {
                int tentativeGScore = gScore[currentNodeId] + neighbour->weight;
                if (tentativeGScore < gScore[neighbour->id]) {
                    gScore[neighbour->id] = tentativeGScore;
                    fScore[neighbour->id] = gScore[neighbour->id] + heuristic(neighbour->id, targetId);
                }
                neighbour = neighbour->nextNeighbour;
            }
        }

        cout << "A* Pathfinding:\n";
        if (fScore[targetId] != INT_MAX) {
            cout << "Shortest path to node " << targetId << " is " << fScore[targetId] << "\n";
        } else {
            cout << "Target not reachable.\n";
        }
    }
};

struct HeapNode {
    int key;
    HeapNode* left;
    HeapNode* right;
    HeapNode* parent;

    HeapNode(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

class MinHeap {
    HeapNode* root;

    void heapifyDown(HeapNode* node) {
        if (!node) return;
        HeapNode* smallest = node;
        if (node->left && node->left->key < smallest->key) smallest = node->left;
        if (node->right && node->right->key < smallest->key) smallest = node->right;
        if (smallest != node) {
            swap(node->key, smallest->key);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(HeapNode* node) {
        while (node->parent && node->key < node->parent->key) {
            swap(node->key, node->parent->key);
            node = node->parent;
        }
    }

    void inorderTraversal(HeapNode* node) {
        if (!node) return;
        inorderTraversal(node->left);
        cout << node->key << " ";
        inorderTraversal(node->right);
    }

    void mergeUtil(HeapNode* source, HeapNode*& target) {
        if (!source) return;
        insert(source->key);
        mergeUtil(source->left, target);
        mergeUtil(source->right, target);
    }

public:
    MinHeap() : root(nullptr) {}

    HeapNode* insert(int key) {
        if (!root) return root = new HeapNode(key);
        HeapNode* current = root;
        HeapNode* parent = nullptr;
        while (current) {
            parent = current;
            if (!current->left) {
                current->left = new HeapNode(key);
                current->left->parent = current;
                heapifyUp(current->left);
                return current->left;
            } else if (!current->right) {
                current->right = new HeapNode(key);
                current->right->parent = current;
                heapifyUp(current->right);
                return current->right;
            }
            current = current->left->key > current->right->key ? current->right : current->left;
        }
        return nullptr;
    }

    int extractMin() {
        if (!root) return INT_MAX;
        int minVal = root->key;
        HeapNode* lastNode = root;
        while (lastNode->left || lastNode->right) lastNode = lastNode->right ? lastNode->right : lastNode->left;
        root->key = lastNode->key;
        if (lastNode->parent && lastNode->parent->left == lastNode) lastNode->parent->left = nullptr;
        else if (lastNode->parent) lastNode->parent->right = nullptr;
        delete lastNode;
        heapifyDown(root);
        return minVal;
    }

    void buildHeap(int arr[], int size) {
        for (int i = 0; i < size; ++i) insert(arr[i]);
    }

    void heapSort(int arr[], int size) {
        buildHeap(arr, size);
        for (int i = 0; i < size; ++i) arr[i] = extractMin();
    }

    void mergeHeaps(MinHeap& other) {
        mergeUtil(other.root, root);
    }

    void print() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    MinHeap minHeap;
    int arr[] = {3, 1, 6, 5, 2, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    minHeap.buildHeap(arr, n);
    minHeap.print();

    int sortedArr[n];
    minHeap.heapSort(arr, n);
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    MinHeap otherHeap;
    int arr2[] = {10, 7, 9};
    int m = sizeof(arr2) / sizeof(arr2[0]);
    otherHeap.buildHeap(arr2, m);

    minHeap.mergeHeaps(otherHeap);
    minHeap.print();

    return 0;
}



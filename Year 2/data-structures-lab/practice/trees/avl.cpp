#include<iostream>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    int height; // To keep track of the height of the node

    Node(int data) {
        this->data = data;
        left = right = NULL;
        height = 1; // New nodes start with a height of 1
    }
};

class AVL {
    Node *root;

public:
    AVL() {
        root = NULL;
    }

    int height(Node *node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node *node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rotateRight(Node *y) {
        Node *x = y->left;
        Node *T = x->right;

        x->right = y;
        y->left = T;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x; // New root
    }

    Node* rotateLeft(Node *x) {
        Node *y = x->right;
        Node *T = y->left;

        y->left = x;
        x->right = T;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y; // New root
    }

    Node* balance(Node *node) {
        int bf = balanceFactor(node);

        // Left heavy
        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left); // Left-Right case
            }
            return rotateRight(node); // Left-Left case
        }

        // Right heavy
        if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right); // Right-Left case
            }
            return rotateLeft(node); // Right-Right case
        }

        return node; // No balancing needed
    }

    Node* insert(Node *node, int data) {
        if (node == NULL) {
            return new Node(data);
        }

        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        } else {
            return node; // Duplicate data not allowed
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        return balance(node);
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void inOrder(Node *node) {
        if (node == NULL) return;

        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void display() {
        inOrder(root);
        cout << endl;
    }
};

int main() {
    AVL tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "In-order Traversal: ";
    tree.display();

    return 0;
}


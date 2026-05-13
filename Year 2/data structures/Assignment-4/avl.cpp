#include <iostream>
using namespace std;

struct Node
{
    Node *left, *right;
    string dicWord;
    int height;

    Node(string dicWord = 0) {
        this->dicWord = dicWord;
        this->left = this->right = NULL;
        this->height = 1;
    }
};

class AVL
{
    Node *root;

    int getMax(int h1, int h2) {
        return (h1 > h2) ? h1 : h2;
    }

    int getHeight(Node *node) {
        if(node == NULL)
            return 0;
        return node->height;
    }

    Node* rightRotate(Node *node) {
        Node *node2 = node->left;
        Node *T2 = node2->right;

        // Perform rotation
        node2->right = node;
        node->left = T2;

        // Update heights
        node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
        node2->height = getMax(getHeight(node2->left), getHeight(node2->right)) + 1;

        // Return new root
        return node2;
    }

    Node* leftRotate(Node *node) {
        Node *node2 = node->right;
        Node *temp = node2->left;

        node2->left = node;
        node->right = temp;

        node->height = 1+ getMax(getHeight(node->left), getHeight(node->right));
        node2->height = 1+ getMax(getHeight(node2->left), getHeight(node2->right));

        return node2;
    }

    int getBalance(Node *node) {
        if (node == NULL)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* insertNode(Node *node, string dicWord) {
        if (node == NULL)
            return new Node(dicWord);
        if (dicWord < node->dicWord)
            node->left = insertNode(node->left, dicWord);
        else if (dicWord > node->dicWord)
            node->right = insertNode(node->right, dicWord);
        else
            return node;

        node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));

        // Get the balance factor
        int balance = getBalance(node);

        // Balance the tree
        // Left Left
        if (balance > 1 && dicWord < node->left->dicWord)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && dicWord > node->right->dicWord)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && dicWord > node->left->dicWord) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && dicWord < node->right->dicWord) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }


    void printAVL(Node *root) {
        if (root == NULL)
            return;
        printAVL(root->left);
        cout << root->dicWord << " ";
        printAVL(root->right);
    }
    Node * removeNode(Node *root, string dicWord) {
        if (root == NULL)
            return root;
        if (dicWord < root->dicWord)
            root->left = removeNode(root->left, dicWord);

        else if (dicWord > root->dicWord)
            root->right = removeNode(root->right, dicWord);

        else {
            // node with only one child or no child
            Node* temp;
            if (root->left == NULL || root->right == NULL) {
                if(root->left == NULL){
                    temp = root->right;
                }
                else temp = root->left;
                //no children
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else // One child case
                    *root = *temp; // copy child
                    delete temp;
                    temp = NULL;
            } else {
                // node with two children: Get the 
                // inorder successor (smallest in 
                // the right subtree)
                Node* temp = getMinValueNode(root->right);

                root->dicWord = temp->dicWord;

                root->right = removeNode(root->right, temp->dicWord);
            }
        }

        if (root == NULL)
            return root;

        root->height = 1 + max(getHeight(root->left), 
                    getHeight(root->right));

        int balance = getBalance(root);

        // Left Left
        if (balance >= 2 && 
            getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right
        if (balance >= 2 && 
            getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right
        if (balance <= -2 && 
            getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left
        if (balance <= -2 && 
            getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node *getMinValueNode(Node *node) {
        Node *current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }
    

public:
    AVL() {
        root = NULL;
    }
    Node *getRoot() {
        return root;
    }
    void remove(string dicWord) {
        this->root = removeNode(this->root, dicWord);
    }

    void insert(string dicWord) {
        this->root = insertNode(this->root, dicWord);
    }

    void print() {
        printAVL(root);
        cout << endl;
    }
    
};

int main() {
    AVL avl;
    avl.insert("all");
    avl.insert("my");
    avl.insert("friends");
    avl.insert("are");
    avl.print();
    avl.insert("heathens");
    avl.insert("take");
    avl.insert("it");
    avl.insert("slow");
    avl.print(); 
    return 0;
}

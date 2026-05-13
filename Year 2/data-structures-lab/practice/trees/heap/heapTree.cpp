#include<iostream>
struct Node{
    Node * left, *right,*parent;
    int data;
    Node(int data){
        this->data = data;
        this->left = this->right = this->parent = nullptr;
    }
};
class HeapTree{
    Node *root;
    HeapTree(){
        root = nullptr;
    }
    ~HeapTree(){
        deleteMax();
    }
    void insertValue(){}
    int deleteMax(){}
    void heapifyB2T(Node *node){
        if (node == NULL || node->parent == NULL) return ;

        if(node -> data > node -> parent -> data){
            swap(node,node->parent);
            heapifyB2T(node->parent);
        }
    }
    void heapify(Node *node){
        if(node ==NULL) return;
        Node*largest = node;
        if(node ->left !=NULL && node ->left->data > largest->data)
        largest = node->left;
        if(node ->right !=NULL && node ->right->data > largest->data)
        largest = node->right;

        if(largest!=node){
            swap(node->data,largest->data);
            heapify(largest);
        }
    }
};

using namespace std;
int main(){
    return 0;
}
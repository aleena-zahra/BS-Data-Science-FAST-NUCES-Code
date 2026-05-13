#include<iostream>
using namespace std;

struct Node{
    int data;
    Node *left;
    Node *right;
    Node(int data){
        left = right = NULL;
        this->data = data; 
    }
};
class Tree{
    Node *root;
    public:
    Tree(){
        root = NULL;
    }
    ~Tree(){
        deleteAllNodes(root);
    }
    void inOrder(Node *root){
        if(root == NULL){
            return;
        }
        inOrder(root->left);
        cout<<root->data<<" ";
        inOrder(root->right);
    }
    void preOrder(Node *root){
        if(root == NULL){
            return;
        }
        cout<<root->data<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
    void postOrder(Node *root){
        if(root == NULL){
            return;
        }
        postOrder(root->left);
        postOrder(root->right);
        cout<<root->data<<" ";
    }
    Node *getRoot(){
        return root;
    }
    void deleteAllNodes(Node *curr){
        if(curr==NULL){
            return;
        }
        deleteAllNodes(curr->left);
        deleteAllNodes(curr->right);
        delete curr;
    }
};

int main(){
    Tree tree;
    Node *temp = tree.getRoot();
    cout<<"root inserted as value 1\n\n";
    temp = new Node(1);
    cout<<"left node inserted as value 2\n\n";
    temp->left = new Node(2);
    cout<<"right inserted as value 3\n\n";
    temp->right = new Node(3);
    cout<<"\nIn order traversal:\n";
    tree.inOrder(temp);
    cout<<"\n\nPreOrder traversal:\n\n";
    tree.preOrder(temp);
    cout<<"\n\nPost Order traversal\n";
    tree.postOrder(temp);


    return 0;
}
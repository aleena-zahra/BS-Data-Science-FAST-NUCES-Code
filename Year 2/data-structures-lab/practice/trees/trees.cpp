#include<iostream>
using namespace std;
struct TreeNode{
    int data;
    TreeNode *right;
    TreeNode *left;
    TreeNode(int data=0){
        this->data=data;
        this->right = this->left = NULL;
    }
    TreeNode(int data, TreeNode *left, TreeNode *right){
        this->data = data;
        this->left = left;
        this->right = right;
    }
    ~TreeNode(){
    }
};

class BinarySearchTree
 {
    TreeNode *root;
    public:
    BinarySearchTree(){
        root = NULL;
    }
    BinarySearchTree( const BinarySearchTree & rhs ){
        //copy constructor 
        TreeNode *rootCopy = rhs.root;
        copyTree(root, rootCopy);
    }
    ~BinarySearchTree( ){
        deleteTree(root);
    }
    void copyTree(TreeNode *root, TreeNode *rhs){
        if(rhs == NULL){
            return;
        }
        root = new TreeNode(rhs->data);
        copyTree(root->left, rhs->left);
        copyTree(root->right, rhs->right);
    }
    void deleteTree(TreeNode *root){
        if(root == NULL){
            return;
        }
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }

    const TreeNode & findMin( ) const{
        TreeNode *temp = root;
        while(temp->left != NULL){
            temp = temp->left;
        }
        return *temp;
    }
    const TreeNode & findMax( ) const{
        TreeNode *temp = root;
        while(temp->right != NULL){
            temp = temp->right;
        }
        return *temp;
    }
    bool contains( const TreeNode & x ) const{
        TreeNode *temp = root;
        while(temp != NULL){
            if(temp->data == x.data){
                return true;
            }
            else if(x.data<temp->data){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
        return false;
    }
    bool isEmpty( ){
        return root == NULL;
    }
    void insert( int data ){
        TreeNode *newNode = new TreeNode(data);
        TreeNode *temp = root;
        if(temp == NULL){
            root = newNode;
            return;
        }
        else if(data<temp->data){
            if(temp->left == NULL){
                temp->left = newNode;
            }
            else{
                temp = temp->left;
            }
        }
        else if(data>temp->data){
            if(temp->right == NULL){
                temp->right = newNode;
            }
            else{
                temp = temp->right;
            }
        }
        else {
            cout<<"Duplicated value, cant insert twice\n";
        }
    }
    TreeNode* removeNode(TreeNode* root, int key){
        //base case
        if(root == NULL){
            return root;
        }
        //if key is smaller than roots value then it lies in left subtree
        if(key<root->data){
            root->left = removeNode(root->left, key);
        }
        //if key is greater than roots value then it lies in right subtree
        else if(key>root->data){
            root->right = removeNode(root->right, key);
        }
        //if data to be deleted has been found
        else if(key==root->data){
            //if leaf node
            if(root->left == NULL && root->right == NULL){
                delete root;
                root = NULL;
            }
            //if one child
            if(root->left == NULL){
                TreeNode *temp =root;
                root = root->right;
                delete temp;
            }
            else if(root->right == NULL){
                TreeNode *temp =root;
                root = root->left;
                delete temp;
            }
            //if two children
            else {
                TreeNode *temp = root->right;
                temp->left = root->left;
                delete root;
            }
        }
    }

    TreeNode * getNode(int data){
        TreeNode *temp = root;
        while(temp != NULL){
            if(temp->data == data){
                return temp;
            }
            else if(data<temp->data){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
        return NULL;
    }
    TreeNode *getRoot(){
        return root;
    }
    friend ostream& operator<<(ostream& output, const BinarySearchTree& other);
    void balance( ){}
};

int main(){
    BinarySearchTree tree;
    TreeNode *root = tree.getRoot();
    tree.insert(25);
    tree.insert(20);
    tree.insert(36);
    tree.insert(10);
    tree.insert(22);
    tree.insert(30);
    tree.insert(40);
    tree.insert(5);
    tree.insert(12);
    tree.insert(28);
    tree.insert(38);
    tree.insert(48);
    tree.removeNode(root,22);
    tree.removeNode(root,40);
    return 0;
}

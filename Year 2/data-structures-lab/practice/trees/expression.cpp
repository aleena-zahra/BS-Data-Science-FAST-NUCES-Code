#include<iostream>
using namespace std;

struct TreeNode{
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int data){
        left = right = NULL;
        this->data = data; 
    }
};
class Tree{
    TreeNode *root;
    public:
    Tree(){
        root = NULL;
    }
    ~Tree(){
        deleteAllNodes(root);
    }
    void inOrder(TreeNode *root){
        if(root == NULL){
            return;
        }
        inOrder(root->left);
        cout<<root->data<<" ";
        inOrder(root->right);
    }
    void preOrder(TreeNode *root){
        if(root == NULL){
            return;
        }
        cout<<root->data<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
    void postOrder(TreeNode *root){
        if(root == NULL){
            return;
        }
        postOrder(root->left);
        postOrder(root->right);
        cout<<root->data<<" ";
    }
    TreeNode *getRoot(){
        return root;
    }
    void deleteAllNodes(TreeNode *curr){
        if(curr==NULL){
            return;
        }
        deleteAllNodes(curr->left);
        deleteAllNodes(curr->right);
        delete curr;
    }
};
struct Node{
    int data;
    Node *link;

    Node(int data){
        this->data = data;
        this->link = NULL;
    }
    ~Node(){
    }
};
class Stack{
    private:
    Node *head;
    public:
    Stack(){
        head = NULL;
    }
    ~Stack(){
        //traverse stack and delete each node until reach null
        Node* current = head;
        while (current != NULL) {
            Node* nextNode = current->link;
            delete current;
            current = nextNode;  
        }
        head = NULL;
    }
    
    void push(int data){
        //create new node and set its values
        Node* newNode = new Node(data);

        if(isEmpty()){
            head = newNode;
        }
        else{
            //when head isnt null store its address in new Node
            newNode->link = head;
            head = newNode;
        }
    }
 

    //delete functions
    int pop(){
        int value;
        if(!isEmpty()){
            Node *temp = head; //store old head/first node
            value = temp->data;
            head = head->link; //new head is next node
            delete temp;      //delete old head/first node
        }
        else {
            cout<<"EMPTY!";
        }
        return value;
    }

    bool isEmpty(){
        return head==NULL;
    }
    void printstack(){
        cout<<endl;
        if(isEmpty()){
            cout<<"EMPTY STACK\n";
            return;
        }
        Node *temp = head;
        while(temp!=NULL){
            cout<<temp->data<<"\n";
            
            temp = temp->link;
            
        }
    }
    //finds if value exists in link, returns index
    int findValueInstack(int data){
        Node *temp = head;
        int index = -1;
        while(temp!=NULL){
            index++;
            if(temp->data ==data){
                break;
            }
            temp = temp->link;
        }
        if(temp!=NULL)
           return index; 
        return -1;
    }
};
int main(){
    Tree tree;
    TreeNode *temp = tree.getRoot();


    return 0;
}
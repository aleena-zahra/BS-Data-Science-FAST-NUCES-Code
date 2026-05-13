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
    ~TreeNode(){}
};
struct Node{
    int data;
    Node *link;
    Node(int data){
        link = NULL; 
    }
    ~Node(){}
};
class Queue
{
private:
    Node *head;

public:
    Queue()
    {
        head = NULL;
    }
    ~Queue()
    {
        // traverse Queue and delete each Node until reach null
        Node *current = head;
        while (current != NULL)
        {
            Node *nextNode = current->link;
            delete current;
            current = nextNode;
        }
        head = NULL;
    }

    
    void enqueue(int data)
    {
        // make the Nodee
        Node *temp = new Node(data);
        // if empty Queue
        if (isEmpty())
        {
            head = temp;
        }
        else
        {
            Node *current = head;
            while (current->link != NULL)
            {
                current = current->link;
            }
            current->link = temp;
        }
        // traverse until current->next ==NULL
    }

    // delete functions
    void dequeue()
    {
        if (!isEmpty())
        {
            Node *temp = head; // store old head/first Node
            head = head->link; // new head is next Node
            delete temp;       // delete old head/first Node
        }
    }
    void peek()
    {
        if (!isEmpty())
        {
            cout << head->data<< "\n";
        }
    }
    bool isEmpty()
    {
        return head == NULL;
    }
    void printQueue()
    {
        cout << endl;
        Node *temp = head;
        while (temp != NULL)
        {
            cout <<temp->data<<"\n";

            temp = temp->link;
        }
        cout << "NULL\n";
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
    void bfs(int data){
        Queue q;
        q.enqueue(root->data);
        while(!q.isEmpty()){
            //deqeue a node and visit it
            //enqueue its children
            if()
        }
    }
};

int main(){
    Tree tree;
    TreeNode *temp = tree.getRoot();
    cout<<"root inserted as value 1\n\n";
    temp = new TreeNode(1);
    cout<<"left node inserted as value 2\n\n";
    temp->left = new TreeNode(2);
    cout<<"right inserted as value 3\n\n";
    temp->right = new TreeNode(3);

    return 0;
}
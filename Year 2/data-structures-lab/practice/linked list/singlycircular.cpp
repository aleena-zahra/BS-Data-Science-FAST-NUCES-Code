#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int data){
        this->data = data;
        next = NULL;
    }

};

class CircularList{
    Node* head;
    Node *tail;
    public:
    CircularList(){
        head = tail = NULL;
    }
    ~CircularList(){
        while(!emptyList()){
            deleteAtHead();
        }
    }
    bool emptyList(){
        return head == NULL;
    }
    void printList(){
        Node *temp = head;
        do{
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        while(temp->next!=head);
    
    }
    void insertAtHead(int data){
        Node *temp = new Node(data);
        if(emptyList()){
            head = tail =temp;
        }
        else {
            temp->next  = head;
        }
        tail->next = head;
    }
    void insertAtTail(int data){
        Node *temp = new Node (data);
        if(emptyList()){
            head = tail = temp;
            tail->next = head;
        }
        else{
            tail->next = temp;
            tail = temp;
            tail->next = head;
        }
    }
    void deleteAtHead(){
        if(emptyList()){
            cout<<"List is empty cant delete\n";
        }
        else if(tail==head){
            delete head;
            tail = head = NULL;
        }
        else{
        Node * tempptr = head;
        head = head->next;
        delete tempptr;
        tail->next = head;

        }
        
    }
    void deleteAtTail(){

        if(emptyList()){
            cout<<"List is empty cant delete";
        }
        else if(tail==head){
            delete head;
            tail = head = NULL;
        }
        else{
            //iterate through list with 2 ptrs
            Node *prev= head;
            Node *curr = head->next;
            while(curr->next!=head){
                prev = curr;
                curr = curr->next;
            }
            delete curr;
            tail = prev;
            tail->next = head;
        }
    }
};
int main(){
    return 0;
}
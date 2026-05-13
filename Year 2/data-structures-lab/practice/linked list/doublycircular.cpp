#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node *prev;
    Node(int data){
        this->data = data;
        next = prev = NULL;
    }

};

class DoublyCircularList{
    Node* head;
    Node *tail;
    public:
    DoublyCircularList(){
        head = tail = NULL;
    }
    ~DoublyCircularList(){
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
        while(temp!=head);
    
    }
    void insertAtHead(int data){
        Node *temp = new Node(data);
        if(emptyList()){
            head = tail = temp;
            tail->next = head;
            head->prev = tail;
        }
        else {
            temp->next = head;
            temp ->prev = tail;
            tail->next = temp;
            head->prev = temp;
            head = temp;
        }
    }
    void insertAtTail(int data){
        Node *temp = new Node (data);
        if(emptyList()){
            head = tail = temp;
            tail->next = head;
            head->prev = tail;
        }
        else{
            temp->prev = tail;
            temp->next = head;
            tail->next = temp;
            head->prev = temp;
            tail= temp;
        }
    }
    void deleteAtHead(){
        if(emptyList()){
            cout<<"List is empty cant delete\n";
        }
        else if(tail==head){
            delete head;
            head = tail = NULL;
        }
        else{
            tail->next= head->next;
            head = head->next;
            delete head->prev;
            head ->prev = tail;
        }
        
    }
    void deleteAtTail(){

        if(emptyList()){
            cout<<"List is empty cant delete";
        }
        else if(tail==head){
            delete head;
            head = tail = NULL;
        }
        else{
            tail = tail->prev;
            head->prev =tail;
            delete tail->next;
            tail->next = head;
        }
    }
};
int main(){
    return 0;
}
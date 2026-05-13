#include <iostream>
using namespace std;

struct Node{
    Node *prev;
    int data;
    Node *next;

    Node(int data){
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
    ~Node(){
        cout<<"\ndestructor called for node with value: "<<this->data;
    }
};
class List{
    private:
    Node *head;
    Node *tail;
    public:
    List(){
        head = tail = NULL;
    }
    ~List(){
        //traverse list and delete each node until reach null
        Node* current = head;
        while (current != NULL) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;  
        }
        head = tail = NULL;
    }
    
    void insertAtHead(int data){
        //create new node and set its values
        Node* newNode = new Node(data);

        if(isEmpty()){
            head = tail = newNode;
        }
        else{

            newNode->next = head;
            head = newNode;
        }
    }
    void insertAtEnd(int data){
        //make the nodee
        Node *newNode = new Node(data);
        //if empty list
        if(isEmpty()){
            head = newNode;
        }
        else{
            newNode->prev = tail;
            tail->next = newNode;
        }
    }
    bool insertAfterPosition(int position,int data){
        
        if(position< 0){
            return false;
        }
        if(position == 0){
            insertAtHead(data);
        }
        
        else{
            Node *newNode = new Node(data);
            int index =0;
            Node *temp = head;
            while(temp->next!=NULL && index<position){
                temp = temp->next;
                index++;
            }
            //at position
            newNode->prev = temp;
            newNode->next = temp->next;
            temp->next = newNode;
            if(newNode->next!=NULL)
            newNode->next->prev = newNode;
            
        }
        return true;
    }
    bool insertAfterValue(int value,int data){
        int index = 0;
        index = findValueInList(value);
        if(index!=-1){
            insertAfterPosition(index,data);
        }
        return false;
    }
    //delete functions
    void deleteAtStart(){
        if(!isEmpty()){
            Node *temp = head; //store old head/first node
            head = head->next; //new head is next node
            delete temp;      //delete old head/first node
            temp= NULL;
        }
    }
    bool deleteAtEnd() {
        if (isEmpty()) {
            return false;
        }
        //only 1 node
        if (head->next == NULL) {
            deleteAtStart();
            return true;
        }
        Node *temp = tail;
        tail = temp->prev;
        tail->next = NULL;
        delete temp;
        temp = NULL;
    }

    bool deleteAtIndex(int position){
        if(position<0){
            return false;
        }
        if(position==0){
            deleteAtStart();
            return true;
        }
        Node *temp = head;
        int index=0;
        while (temp->next->next != NULL && index<position) {
            temp = temp->next;
            index++;
        }
        // Delete the node
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;

        delete temp;
        temp = NULL;
        return true;
    }
    bool deleteAtValue(int value){
        if(head->data == value){
            deleteAtStart();
            return true;
        }
        Node *temp = head;

        while (temp->next->next != NULL && temp->data!=value) {
            temp = temp->next;
        }
        // Delete the node
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        delete temp;
        temp = NULL;
        return true;
    }

    bool isEmpty(){
        return head==NULL && tail==NULL;
    }
    void print(){
        cout<<endl;
        Node *temp = head;
        cout<<"NULL <- ";
        while(temp!=NULL){
            cout<<temp->data<<" -> <- ";
            
            temp = temp->next;
            
        }
        cout<<"NULL\n";
    }
    //finds if value exists in next, returns index
    int findValueInList(int data){
        Node *temp = head;
        int index = -1;
        while(temp!=NULL){
            index++;
            if(temp->data ==data){
                break;
            }
            temp = temp->next;
        }
        if(temp!=NULL)
           return index; 
        return -1;
    }
    Node *reverse(Node * curr){
        if(curr==NULL){
            return NULL;
        }
        //swapping
        Node *temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        if(curr->prev == NULL){
            return curr; // this is head now
        }
        return reverse(curr->prev);
    }
    Node *reverse(){
        if(head==NULL || head->next==NULL){
            return head;
        }
        Node *curr= head, *prev = NULL;

        while(curr!=NULL){
            prev = curr->prev;
            curr->prev = curr->next;
            curr->next = prev;
            curr = curr->prev;
        }
        return prev->prev;
    }
   
};
int main(){
    List list;
    list.insertAtHead(10);
    list.print();
    cout<<"Value exists at index "<<list.findValueInList(10)<<"\n\n";
    list.insertAtHead(2);
    list.print();
    list.insertAtHead(1);
    list.print();
    list.insertAtEnd(7);
    list.print();
    list.insertAfterPosition(2,100);
    list.print();
    list.deleteAtEnd();
    list.print();
    list.insertAfterValue(2,66);
    list.print();
    //list.deleteAtIndex(2); //get rid of 2nd index (3rd node)
    list.deleteAtValue(66);
    list.print();
    cout<<endl;
    return 0;
}
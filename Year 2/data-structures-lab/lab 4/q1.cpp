#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *link;

    Node(int data){
        this->data = data;
        this->link = NULL;
    }
    ~Node(){
        cout<<this->data<<" Destroyed\n";
    }
};
class List{
    private:
    Node *head;
    public:
    List(){
        head = NULL;
    }
    ~List(){
        //traverse list and delete each node until reach null
        Node* current = head;
        while (current != NULL) {
            Node* nextNode = current->link;
            delete current;
            current = nextNode;  
        }
        head = NULL;
    }
    
    void insertAtHead(int data){
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
    void insertAtEnd(int data){
        //make the nodee
        Node *temp = new Node(data);
        //if empty list
        if(isEmpty()){
            head = temp;
        }
        else{
            Node *current = head;
            while(current->link !=NULL){
                current = current->link;
            }
            current->link = temp;
        }
        //traverse until current->next ==NULL
    }
 
    //delete functions
    void deleteAtStart(){
        if(!isEmpty()){
            Node *temp = head; //store old head/first node
            head = head->link; //new head is next node
            delete temp;      //delete old head/first node
        }
    }
    bool deleteAtEnd() {
        if (isEmpty()) {
            return false;
        }
        //only 1 node
        if (head->link == NULL) {
            deleteAtStart();
            return true;
        }
        //delete from end when nodes>1
        
        Node* secondLast = head;
        while (secondLast->link->link != NULL) {
            secondLast = secondLast->link;
        }

        // Delete the last node
        delete (secondLast->link);

        // Change link of second last
        secondLast->link = NULL;
        return true;
    }


    bool deleteAtValue(int value){
        if(head->data == value){
            deleteAtStart();
            return true;
        }
        Node *current = head;
        Node *previous = NULL;

        while (current->link->link != NULL && current->data!=value) {
            previous = current;
            current = current->link;
        }
        previous->link = current->link;
        // Delete the node
        delete current;
        return true;
    }

    bool isEmpty(){
        return head==NULL;
    }
    void printList(){
        cout<<endl;
        Node *temp = head;
        while(temp!=NULL){
            cout<<temp->data<<" -> ";
            
            temp = temp->link;
            
        }
        cout<<"NULL\n";
    }
    //finds if value exists in link, returns index
    int findValueInList(int data){
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
    List list;
    list.insertAtHead(2);
    cout<<"Value exists at index "<<list.findValueInList(10)<<"\n\n";
    list.insertAtHead(5);
    list.insertAtHead(8);
    list.insertAtEnd(12);
    cout<<"initially the list is:\n";
    list.printList();
    list.deleteAtEnd();
    list.deleteAtStart();
    list.deleteAtValue(5);
    list.printList();
    cout<<endl;
    return 0;
}

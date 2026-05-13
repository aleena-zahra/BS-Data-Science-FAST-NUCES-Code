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
    Stack stack;
    int value=0;
    for(int i =0 ; i<3;i++){
        cout<<"Enter value "<<i+1<<"\n";
        cin>>value;
        stack.push(value);
    }
    //stack.printstack();
    cout<<"Values reversed are:\n";
    cout<<stack.pop()<<"\n";
    cout<<stack.pop()<<"\n";
    cout<<stack.pop()<<"\n";
    stack.printstack();
    cout<<endl;
    return 0;
}

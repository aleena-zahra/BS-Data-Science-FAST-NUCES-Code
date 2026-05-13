#include <iostream>
using namespace std;

struct Node{
    int pageID;
    Node *link;

    Node(int pageID=0){
        this->pageID = pageID;
        this->link = NULL;
    }
    ~Node(){
    }
    void print(){
        cout<<this->pageID<<"\n";
    }
};
class Stack{
    private:
    Node *arr;
    int size;
    int length;
    public:
    Stack(){
        size = 30;
        length =0;
        arr = new Node[size];
    }
    ~Stack(){
        delete [] arr;
    }
    
    void push(int pageID){

        if(isFull()){
            cout<<"Cant push anymore";
        }
        else{
            arr[length++] = pageID;
        }
    }
 

    //delete functions
    int pop(){
        int value;
        if(isEmpty()){
            cout<<"cant delete stack is empty";
        }
        else {
            //shift values to the left
            for(int i = 1 ; i<length ; i++)
            arr[i-1] = arr[i];
            length--;
        }
        return value;
    }

    bool isEmpty(){
        return arr==NULL;
    }
    bool isFull(){
        return length==size-1;
    }
    void printstack(){
        cout<<endl;
        if(isEmpty()){
            cout<<"EMPTY STACK\n";
            return;
        }
        for(int i =0 ; i<length ;i++){
            arr[i].print();
        }
    }
    int peek(){
        return arr[0].pageID;
    }
};
int main(){
    Stack stack;
    int page=0;
    for(int i =0 ; i<3;i++){
        cout<<"Enter page visited "<<i+1<<"\n";
        cin>>page;
        stack.push(page);
    }
    stack.printstack();
    stack.pop();
    stack.printstack();
    stack.pop();
    stack.printstack();
    stack.pop();
    stack.printstack();
    cout<<endl;
    return 0;
}
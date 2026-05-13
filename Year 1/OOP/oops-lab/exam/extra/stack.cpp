#include <iostream>
using namespace std;

const int max_size = 100;
class stack{
    public:
    int top;
    int* arr;
    
    stack(){
        top=-1;
        arr = new int[max_size];
    }
    void push(int a){
        if(top==max_size-1){
            cout<<"Stack Overflow";
            return;
        }
        else {
            arr[++top]=a;
            return;
        }
    }
    void pop(){
        if(isEmpty()){
            cout<<"Stack underflow\n";
            return;
        }
        else{
            top--;
        }
    }
    int peek(){
        if(isEmpty()){
            cout<<"Empty stack\n";
            return -1;
        }
        else return arr[top];
    }
    bool isEmpty(){
        return top==-1;
    }

};
int main(){
    stack s1;
    s1.push(1);
    s1.push(5);
    s1.pop();
    cout<<s1.peek()<<endl;
    s1.pop();
    cout<<s1.top<<endl;
    cout<<s1.peek()<<endl;
    s1.pop();
}

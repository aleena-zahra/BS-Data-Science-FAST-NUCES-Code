#include <iostream>
using namespace std;

const int MAX_SIZE = 100; // Maximum size of the queue

class Queue {
    private:
    int *arr;
    int front,rear;
    public:
    Queue(){
        front=-1,rear=-1;
        arr= new int [MAX_SIZE];
    }
    void enqueue(int a){
        if(rear==MAX_SIZE-1){
            cout<<"Queue overflow\n";
            return;
        }
        else if(isEmpty()){
            front++;
        }
            arr[++rear]=a;
            return;
    }
    void dequeue(){
        if(isEmpty()){
            cout<<"Queue underflow\n";
            return;
        }
        if(front==rear){
            front++,rear++;
        }
        else front++;
    }
    int peek(){
        if(isEmpty()){
            cout<<"Queue is empty\n";
            return -1;
        }
        else return arr[front];

    }
    bool isEmpty(){
        return front==-1;
    }
};

int main() {
    Queue queue;

    // Enqueueing elements into the queue
    queue.enqueue(5);
    queue.enqueue(10);
    queue.enqueue(15);

    // Peeking and dequeuing elements from the queue
    cout << "Front element: " << queue.peek() << endl;
    queue.dequeue();
    cout << "Front element after dequeue: " << queue.peek() << endl;

    return 0;
}

#include<iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
    Node(int data){
        this->data = data;
        next=NULL;
    }
    ~Node(){
        next = NULL;
    }
};
class List{
    Node *head;
    int length;
    List(const List & other){}
    public:
    List(){
        head = NULL;
        length = 0;
    }
    ~List(){
        Node *temp = head;
        while(temp!=NULL){
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
    }
    //insertion
      //at head
      void push(int data){
        Node *newNode = new Node(data);
        length++;
        if(head==NULL){
            head = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
      }
      //at tail
      void enqueue(int data){
        length++;
        Node *newNode = new Node(data);
        if(head==NULL){
            head = newNode;
            return;
        }
        Node *temp = head;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = newNode;
      }
      //at value
      void insertBeforeValue(int value,int data){
        Node *newNode = new Node(data);
        Node *temp = head;
        bool flag = false;
        while(temp->next!=NULL){
            if(temp->next->data == value){
                flag = true;
                length++;
                newNode->next = temp->next;
                temp->next = newNode;
            }
            temp = temp->next;
        }
        if(!flag){
            cout<<"value not found";
        }
      }
      void insertAfterValue(int value,int data){
        Node *newNode = new Node(data);
        Node *temp = head;
        while(temp!=NULL){
            if(temp->data == value){
                length++;
                newNode->next = temp->next;
                temp->next = newNode;
            }
            temp = temp->next;
        }
      }
      //at index
      void insertAtIndex(int index,int data){
        if(index==0){
            push(data);
            return;
        }
        Node *newNode = new Node(data);
        Node *temp = head;
        int count =0;
        while(temp!=NULL && count<index-1){
            temp= temp->next;
            count++;
        }
        if(count==index-1){
            length++;
            newNode->next = temp->next;
            temp->next = newNode;
        }
        if(temp==NULL){
            cout<<"length be to showt";
        }
      }
    //deletion
      //at head
      void dequeue(){
        if(head==NULL){
            cout<<"no item left to dequeue";
            return;
        }
        Node *temp = head;
        head = head->next;
        delete temp;
        length--;
      }
      //at tail
      void pop(){
        if(head==NULL){
            cout<<"List is empty, cant delete";
        }
        if(head->next==NULL){
            dequeue();
            return;
        }
        Node *curr = head;
        Node *prev = NULL;
        while(curr->next!=NULL){
            prev = curr;
            curr= curr->next;
        }
        prev->next = NULL;
        delete curr;
        length--;

      }
      void deleteValue(int value){
        //at head
        if(head->data==value){
            Node *temp = head;
            head = head->next;
            delete temp;
            length--;
        }
        Node *curr=head,*prev=NULL;
        bool flag = false;
        while(curr->next!=NULL){
            if(curr->data==value){
                flag = true;
                Node *temp = curr;
                prev->next = curr->next;
                delete temp;
                length--;
                break;
            }
            prev = curr;
            curr = curr->next;
            
        }
        if(!flag){
            cout<<"value not found";
        }
      }
      //at index
    void deleteIndex(int index){
        if(index==0){
            dequeue();
            return;
        }
        if(index>=length){
            return;
        }
        int count =0;
        Node *temp = head->next;
        while(temp->next!=NULL && count<index-1){
            temp = temp->next;
        }
        Node *temp2 = temp->next;
        temp->next = temp->next->next;
        delete temp2;
    }
    //print
    void print(){
        Node *temp = head;
        while(temp!=NULL){
            cout<<temp->data<<" -> ";
            temp = temp->next;
        }
        cout<<"NULL\n";
    }
    //isempty
    bool isEmpty(){
        return head==NULL;
    }
    //other functions
    void reverseList(){
        Node *prev=NULL,*curr=head,*after=head->next;
        while(curr!=NULL){
            after = curr->next;
            curr->next = prev; //reverse
            prev = curr;
            curr = after;
        }
    }
    Node * returnMiddle(Node *head){
        Node *slow= head, *fast=head;
        while(slow!=NULL && fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast= fast->next->next;
        }
        return slow;
    }
    Node *rotate(Node *head, int k){
        if(k==0 || head==NULL){
            return head;
        }
        Node *curr = head;
        int length = 1;
        while(curr->next!=NULL){
            curr = curr->next;
            length++;
        }
        k = k%length;
        if(k==0){
            return head;
        }
        curr->next = head;//making list circular
        //find new head at kth +1 node
        curr = head;
        for (int i = 1; i < k; i++)
             curr = curr->next;
        head = curr->next;
        curr->next = NULL;
        return head;
    }
    //sort using merge sort
    // Merge Sort function for linked list
    Node* mergeSort(Node* head) {
        if (!head || !head->next) return head;

        // Split the list into halves
        Node* middle = returnMiddle(head);
        Node* left = head;
        Node* right = middle->next;
        middle->next = nullptr;  // Split the list

        // Recursively sort each half
        left = mergeSort(left);
        right = mergeSort(right);

        // Merge the sorted halves
        return merge(left, right);
    }
    Node* merge(Node* left, Node* right) {
        if (left==NULL) return right;
        if (right==NULL) return left;

        if (left->data < right->data) {
            left->next = merge(left->next, right);
            return left;
        } else {
            right->next = merge(left, right->next);
            return right;
        }
    }

};
int main(){
    List l;
    l.push(1);
    l.push(0);
    l.insertAfterValue(1,3);
    l.insertBeforeValue(3,2);
    l.insertAtIndex(4,4);
    l.enqueue(5);
    l.print();
    return 0;
}
//Visit New Site: Add a new website to the history list. When a new site is visited, it
// should be placed after the current website, and the current position should move to this
// new site.
// 2. Go Back: Move backward in history.
// 3. Go Forward: Move forward in history.
// 4. Display History: Print all visited websites starting from the current site.
#include<iostream>
using namespace std;

struct Node{
    string url;
    Node* next;
    Node *prev;
    Node(string url){
        this->url = url;
        next = prev = NULL;
    }

};

class DoublyCircularList{
    Node* head;
    Node *tail;
    Node *curr;
    public:
    DoublyCircularList(){
        head = tail = curr = NULL;
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
        cout<<"\n\n\nPrinting Visited websites: \n";
        Node *temp = head;
        do{
            cout<<temp->url<<" -> ";
            temp = temp->next;
        }
        while(temp!=head);
        cout<<"back to head \n";  
        cout<<"Current is at "<<curr->url<<endl;
    }
    void goBack(){
        if(emptyList()){
            cout<<"List is empty cant go back\n";
        }
        else{
            curr = curr->prev;
        }
    }
    void goForward(){
        if(emptyList()){
            cout<<"List is empty cant go forward\n";
        }
        else{
            curr = curr->next;
        }
    }
    void insertAtHead(string url){
        Node *temp = new Node(url);
        if(emptyList()){
            head = tail = curr = temp;
            tail->next = head;
            head->prev = tail;
        }
        else {
            temp->next = head;
            temp ->prev = tail;
            tail->next = temp;
            head->prev = temp;
            head = curr = temp;
        }
    }
    void insertAtTail(string url){
        Node *temp = new Node (url);
        if(emptyList()){
            head = tail = curr = temp;
            tail->next = head;
            head->prev = tail;
        }
        else{
            temp->prev = tail;
            temp->next = head;
            tail->next = temp;
            head->prev = temp;
            tail= curr= temp;
        }
    }
    void insertHistory(string url){
        Node *temp = new Node(url);
        if(emptyList()){
            head = tail = curr = temp;
            tail->next = head;
            head->prev = tail;
        }
        else if(curr==head){
            insertAtHead(url);
        }
        else if(curr==tail){
            insertAtTail(url);
        }
        else {
            Node *ptr = curr->next;
            temp->next = ptr;
            temp->prev = curr;
            curr->next = temp;
            ptr->prev = temp;
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
  
 
};
int main(){
    DoublyCircularList history;
// Visit 5 websites in the following order:
// ○ Website 1: "google.com"
// ○ Website 2: "stackoverflow.com"
// ○ Website 3: "github.com"
// ○ Website 4: "reddit.com"
// ○ Website 5: "medium.com"
    history.insertAtTail("google.com");
    history.insertAtTail("stackoverflow.com");
    history.insertAtTail("github.com");
    history.insertAtTail("reddit.com");
    history.insertAtTail("medium.com");
    history.printList();
// 2. Go back twice.
    history.goBack();
    history.goBack();
    history.printList();
// 3. Visit a new website "news.com".
    history.insertAtTail("news.com");
    history.printList();
// 4. Go forward once.
    history.goForward();
// 5. Display the current browsing history
    history.printList();
    return 0;
}
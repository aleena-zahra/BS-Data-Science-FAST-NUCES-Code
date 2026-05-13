#include<iostream>
using namespace std;

struct Node{
    int ID;
    string name;
    Node* next;
    Node(int ID,string name){
        this->ID = ID;
        this->name = name;
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
        cout<<"Songs in the playlist: \n";
        Node *temp = head;
        do{
            cout<<temp->ID<<" "<<temp->name<<" -> ";
            temp = temp->next;
        }
        while(temp->next!=head);
        cout<<"(back to head)"<<endl;
    
    }
    void addSongAtTail(int ID, string name){
        Node *temp = new Node (ID,name);
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
        cout<<"Played "<<tempptr->name<<endl;
        delete tempptr;
        tail->next = head;

        }
        
    }
    Node *getNext(Node *curr){
        return curr->next;
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
            cout<<"Played "<<curr->name<<endl;
            delete curr;
            tail = prev;
            tail->next = head;
        }
    }
    void deleteSongAtValue(int ID){
        //find node with value = ID
        Node *prev = head;
        Node *curr = head->next;
        while(curr!=head && curr->ID!=ID){
            prev = curr;
            curr = curr->next;
        }
        if(curr==head){
            cout<<"ID not found\n";
        }
        else if(curr==head){
            deleteAtHead();
        }
        else if(curr==tail){
            deleteAtTail();
        }
        else{
            prev->next = curr->next;
            cout<<"Played "<<curr->name<<endl;
            delete curr;
        }
    }
};
int main(){
    //Add 5 songs to the playlist:
    // ○ Song 1: songID = 101, songName = "Song A"

    // ○ Song 2: songID = 102, songName = "Song B"
    // ○ Song 3: songID = 103, songName = "Song C"
    // ○ Song 4: songID = 104, songName = "Song D"
    // ○ Song 5: songID = 105, songName = "Song E"
    // 2. Display the current playlist.
    // 3. Remove the song with songID = 103.
    // 4. Simulate playing the next 3 songs starting from "Song A".
    // 5. Display the updated playlist.
    CircularList playlist;
    playlist.addSongAtTail(101,"Song A");
    playlist.addSongAtTail(102,"Song B");
    playlist.addSongAtTail(103,"Song C");
    playlist.addSongAtTail(104,"Song D");
    playlist.addSongAtTail(105,"Song E");
    playlist.printList();
    playlist.deleteSongAtValue(103);
    cout<<"Playlist after deleting song with ID 103\n";
    playlist.printList();
    cout<<"Playing next 3 songs\n";
    playlist.deleteAtHead();
    playlist.deleteAtHead();
    playlist.deleteAtHead();
    playlist.printList();
    return 0;
}
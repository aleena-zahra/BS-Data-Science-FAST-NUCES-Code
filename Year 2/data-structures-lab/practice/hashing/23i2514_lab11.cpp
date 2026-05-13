#include<iostream>
using namespace std;


class Hashtable{
    public:
    int *arr;
    int size;
    Hashtable(int size=10){
        this->size = size;
        arr = new int[size];
        for(int i=0;i<size;i++){
            arr[i] = -1; //initialized with value that isnt possible
        }
    }
    void insert(int value,int choice){
        if(choice == 1)
            insertLinearProbing(value);
        else if(choice == 2)
            insertQuadraticProbing(value);
        else if(choice == 3)
            insertRandomProbing(value);
    }
    void insertLinearProbing(int value){
        int index = value%size;
        if(arr[index] == -1){
            arr[index] = value;
        }
        else{
            for(int i=index+1;i<size;i++){
                if(arr[i] == -1){
                    arr[i] = value;
                    return;
                }
            }
        }
        
    }
    void insertQuadraticProbing(int value) {
        
    int index = value % size;
    if(arr[index] == -1){
            arr[index] = value;
        }
    else{
    int i = 1;
    while (arr[(index + i * i) % size] != -1) {
        i++;
    }
    arr[(index + i * i) % size] = value;
    }
}

void insertRandomProbing(int value) {
    int index = value % size;
    if(arr[index] == -1){
            arr[index] = value;
        }
    else{
    srand(time(0));
    int i = 1;
    while (arr[(index + rand() % size) % size] != -1) {
        i++;
    }
    arr[(index + rand() % size) % size] = value;
    }
}
    void display(){
        for(int i=0;i<size;i++){
            cout<<arr[i]<<" \n";
        }
        cout<<endl;
    }
       void search(int value){
        int index = value%size;
        if(arr[index] == value){
            cout<<"Value found at index: "<<index<<endl;
        }
        else{
            for(int i=index+1;i<size;i++){
                if(arr[i] == value){
                    cout<<"Value found at index: "<<i<<endl;
                    return;
                }
            }
        }
    }
    // ~Hashtable(){
    //     delete [] arr;
    // }
};
class HashtableMenu{
    private:
    Hashtable h;
    bool exited;
    public:
    HashtableMenu(int size){
        h = Hashtable(size);
        exited = false;
    }
    void showMenu(){
        int choice;
        cout<<"This is a hash table menu\n";
        cout<<"Enter digit corresponding to what you want to do\n";
        while(!exited){
            cout<<"1. Insert\n2. Search\n3. Display\n4. Exit\n";
            cin>>choice;
            switch(choice){
                case 1:
                    int key;
                    cout<<"Enter key: ";
                    cin>>key;
                    cout<<"1. Insert with Linear Probing\n2. Insert with Quadratic Probing\n3. Insert with Random Probing\n";
                    cin>>choice;  
                    h.insert(key,choice);
                    break;
                case 2:
                    cout<<"Enter key: ";
                    cin>>key;
                    h.search(key);
                    break;
                case 3:
                    h.display();
                    break;
                case 4:
                    exited = true;
                    return;
            }
        }
    }
};
int main(){
    HashtableMenu h(10);
    h.showMenu();
    return 0;
}

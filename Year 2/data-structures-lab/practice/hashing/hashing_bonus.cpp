#include "linked_list.cpp"
#include <iostream>

class HashTable
{
private:
    List **table; //array of linked lists
    int size;
public:
    HashTable(int size){
        this->size = size;
        //dma for the table
        table = new List*[size];
        for(int i=0;i<size;i++){
            table[i] = new List(); //initially the list is empty
        }
    }
    ~HashTable(){
        for(int i=0;i<size;i++){
            delete table[i];
        }
        delete[] table;
    }
    void printHashTable() {
        for (int i = 0; i < size; i++) {
            cout << "Bucket " << i << ": ";
            table[i]->printList();
        }
    }
    int getHashTableFunction(int key){
        return key%size;
    }
    void insert(int key, int value) {
        int index = getHashTableFunction(key);
        if(table[index]->findValueInList(value)!=-1){
            cout<<"Duplicate found during insertion\n";
            return;
        }
        table[index]->insertAtEnd(value);
    }
    bool search(int key, int value) {
        int index = getHashTableFunction(key);
        return table[index]->findValueInList(value);
    }
    void remove(int key, int value) {
        int index = getHashTableFunction(key);
        table[index]->deleteAtValue(value);
    }
};
int main(){
    HashTable ht(10);
    ht.insert(1,100);
    ht.insert(1,24);
    ht.insert(2,200);
    ht.insert(3,300);
    ht.printHashTable();
    return 0;
}
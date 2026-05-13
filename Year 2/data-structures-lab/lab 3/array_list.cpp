#include <iostream>
using namespace std;

//class template 
template <typename T>
class List {
private:
    T* list;           // Dynamic array to store the list elements
    int capacity;      // Maximum capacity of the list
    int length;        // Current number of elements in the list

    void resize() {
        // Resize the array to double its current size
        T* newList = new T[capacity * 2];
        for (int i = 0; i < length; i++) {
            newList[i] = list[i];
        }
        delete[] list;
        list = newList;
        capacity *= 2;
    }

public:
    // Constructor to initialize the list with a fixed capacity
    List(int initialSize = 100) {
        capacity = initialSize;
        list = new T[capacity];
        length = 0;
    }

    // Destructor to free the dynamically allocated memory
    // ~List() {
    //     delete[] list;
    // }
    //Shift array elements to the right ---ahead
    void shiftElementsToRight(int position){
        for(int i =position ; i<length ; i++){
            T temp = list[i];
            list[i] = list[i+1];
            list[i+1] = temp;
        }

    }
    void shiftElementsToLeft(int position){
        for(int i =position ; i<length ; i++){
            list[i-1] = list[i];


        }

    }
    // Insert an element at a specific position (0-based index)
    void insert(int position, T value) {
        if(position<capacity){
            shiftElementsToRight(position);
            list[position]=value;
            length++;
        }
        else cout<<"Position is greater than capacity";
    }

    // Delete an element by its value (first occurrence)
    bool deleteByValue(T value) {
        
        for(int i =0 ; i<length ; i++){
            if(list[i]==value){
                deleteByPosition(i);
                return 1;
            }
        }
        return 0;
    }

    // Delete an element by its position (0-based index)
    bool deleteByPosition(int position) {
        bool found = false;
        if(position<capacity){
            found = true;
            shiftElementsToLeft(position);
            length--;
        }
        return found;
    }

    // Search for an element by its value, return the position if found, otherwise -1
    int search(T value) {
        
        for(int i =0 ; i<length ; i++){
            if(list[i]==value){
                return i;
            }
        }
        return -1;
    }

    // Access an element by its position (0-based index)
    T access(int position) {
        
        return list[position];  
         
    }

    // Return the current number of elements in the list
    int size() {
       
        return length;
    }

    // Check if the list is empty
    bool isEmpty() {
       return length==0;
         
    }

    // Display the elements of the list
    void display() {
       for(int i =0 ; i<length ; i++){
           cout<<list[i]<<"  ";
       }
        cout<<endl;
    }
};


int main() {
    List <int>list;
    if(list.isEmpty()){
        cout<<"List is empty currently";
    }
    list.insert(0,1);
    list.insert(1,2);
    list.display();
    list.insert(1,3);
    list.display();
    list.deleteByPosition(0);
    list.display();
    list.deleteByValue(2);
    cout<<"at the end size is"<<list.size();
    // write code to test functionalities 
    
    return 0;
}
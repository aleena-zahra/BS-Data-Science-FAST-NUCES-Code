#include <iostream>
using namespace std;
class ResizableArray
{
private:
    int *elements;
    int size;
    int capacity;

public:
    ResizableArray()
    {
        size = 0;
        capacity = 1;
        elements = new int[capacity];
    };
    ResizableArray(int *element, int size, int capacity)
    {
        this->size = size;
        this->capacity = capacity;
        this->elements = new int[capacity];
        for (int i = 0; i < size; i++)
        {
            this->elements[i] = element[i];
        }
    }
    ResizableArray(const ResizableArray &copy)
    {
        this->capacity = copy.capacity;
        this->size = copy.size;
        this->elements = new int[capacity];
        for (int i = 0; i < this->size; i++)
        {
            this->elements[i] = copy.elements[i];
        }
    }
    void increaseArraySize()
    {
        cout << "increasing size of arr as capacity is " << capacity << endl;
        int newCapacity = this->capacity * 2;
        ResizableArray temp(this->elements, this->size, newCapacity);
        delete[] elements;
        this->elements = temp.elements;
        this->capacity = temp.capacity;
        this->size = temp.size;
    }
    // Add value to the end of the array.
    void add(int value)
    {
        size = size + 1;
        if (size <= capacity)
        {
            elements[size-1] = value;
        }
        else
        {
            //
            increaseArraySize();
            elements[size-1] = value;
            display();
        }
    }
    void shiftToRight(int index){
        for (int i = size-1 ; i>index ; i--){
            elements[i+1] = elements[i];
        }
    }
    bool insert(int index, int value)
    {
        if (index >= capacity)
            return false;
        else if (index == capacity - 1)
        {
            add(value);
        }
        else{
            //shift values ahead of index to the right
            shiftToRight(index+1);
            elements[index] = value;
            size++;
        }
        return true;
    }
    bool remove(int index) {
        if(index>=capacity) return false;
        for (int i = index ; i<size ; i++){
            elements[i] = elements[i+1];
        }
        return true;
    }
    bool update(int index, int value) {
        elements[index]= value;
    }

    // Return the value at the specified index.
    // If the index is out of bounds, return -1.
    int get(int index) const
    {
        if (index >= size)
        {
            return -1;
        }
        return elements[index];
    }
    int getSize() const
    {
        return this->size;
    }
    void reverseArrayInPlace(int start, int end)
{
    while (start < end) {
        int temp = elements[start];
        elements[start] = elements[end];
        elements[end] = temp;
        start= start+1;
        end = end -1;
    }
}
    void reverse()
    {
        reverseArrayInPlace(0,size-1);
    }
    // Return the index of the first occurrence
    // of value in the array. If value is not found, return -1.
    int find(int value) const
    {
        for (int i = 0; i < size; i++)
        {
            if (elements[i] == value)
            {
                return i;
            }
        }
        return -1;
    }
    void display()
    {
        cout << "Array is {  ";
        for (int i = 0; i < size; i++)
        {
            cout << elements[i] << "  ";
        }
        cout << "}\n";
    }
};
int main()
{
    ResizableArray arr1;
    arr1.add(2);
    arr1.add(3);
    arr1.add(1);
    arr1.insert(1,6);
    arr1.display();
    arr1.reverse();
    arr1.display();
    arr1.remove(1);
    arr1.display();
    return 0;
}
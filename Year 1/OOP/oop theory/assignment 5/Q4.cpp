#include <iostream>
using namespace std;
class Set
{
private:
    int *elements;
    int size;

public:
    Set(){
        elements = nullptr;
        size =0;
    };
    Set(int *element, int size){ 
        this->size = size; 
        this->elements = new int[size]; 
        for (int i = 0; i < size; i++) {
            this->elements[i] = element[i]; 
        }
    }
    Set(const Set &copy){
        this->size = copy.size; 
        this->elements = new int[size];
        for (int i = 0; i < this->size; i++) {
            this->elements[i] = copy.elements[i]; 
        }
    } 
    Set operator = (const Set &val){
        this->size = val.size; 
        this->elements = new int[size];
        for (int i = 0; i < this->size; i++) {
            this->elements[i] = val.elements[i]; 
        }
        return *this;
    }
    Set operator+(const Set &val) const{ // Union
        int * tempArr;
        tempArr = new int[size+val.size];
        for(int i =0 ; i<size ; i++){
            tempArr[i] = this->elements[i];
        }
        int index =size;
        for(int i =0 ; i<val.size ; i++){
            int num = val.elements[i];
            if(find( num )==-1 ) {
                tempArr[index] = num;
                index++;
            }
        }
        Set tempSet(tempArr, index);
        delete[] tempArr;
        return tempSet;
    }
    Set operator*(const Set &val) const{ // Intersection
        int tempSize = this->size + val.size;
        int * tempArr = new int[tempSize];
        int index=0;
        for(int i = 0 ; i<val.size ; i++){
            int element = val.elements[i];
            if(find(element)!=-1){
                tempArr[index] =  element;
                index++;
            }
        }
        if(index==0) {
        cout<<"No intersection\n";
    }
        Set tempSet(tempArr, index);
        delete[] tempArr;
        return tempSet;
    }
    Set operator-(const Set &val) const{ // Difference
    int tempSize = this->size;
    int *tempArr = new int[tempSize];
    int index=0;
    for (int i = 0; i < this->size; i++) {
        int num = this->elements[i];
        if (val.find(num)==-1) {
            tempArr[index++] = num;
        }
    }
    if(index==0) {
        cout<<"No difference\n";
    }
    Set tempSet(tempArr, index);
    delete[] tempArr;
    return tempSet;
    }
    // Compound Assignment Operators
    Set &operator+=(const Set &rhs){ // Union Assignment
        *this = *this + rhs;
        return *this;
    }
    Set &operator*=(const Set &rhs){ // Intersection Assignment
        *this = *this * rhs;
        cout<<"Intersection Assignment";
        cout<<*this;
        return *this;
    }
    Set &operator-=(const Set &rhs){ // Difference Assignment
        *this = *this - rhs;
        cout<<"Difference Assignment";
        cout<<*this;
        return *this;
    }
    // Logical Operators
    bool operator==(const Set &val) const{
        if(this->size!=val.size) return false;
        for(int i = 0 ; i<val.size ; i++){
            if(elements[i]!=val.elements[i]){
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Set &val) const{
        return !(*this==val);
    }
    //  Functional Operators
    Set &operator>(Set &){ //sort elemtns
    for (int i = 0; i < this-> size - 1; i++) {
        for (int j = 0; j < this-> size - i - 1; j++) {
            if (this-> elements[j] > this-> elements[j + 1]) {
                int temp = this-> elements[j];
                this-> elements[j] = this-> elements[j + 1];
                this-> elements[j + 1] = temp;
            }
        }
    }
    return *this;
}
    int &operator[](int element);             // Access element at index
    bool operator()(int element) const{ // Check if element is in the set
        for (int i =0 ; i<size ; i++){
            if(element ==elements[i]){
                return true;
            }
        }
        return false;
    }              
    
    bool operator()(int element, int dumy){ // Add element to the set if it is not already in set, 
    if (!(*this)(element)){
        int tempSize = this->size +1;
        int *tem = new int[tempSize];
        for (int i = 0; i < tempSize; i++) {
            tem[i] = elements[i]; 
        }
        tem[size]=element;
        delete[] elements; 
        this->elements = tem; 
        size++;
        return true;
    }
    return false;
    }         
    
    bool operator()(int element, int dumy, int dumy2){
    // Add element to the set if it is not already in set and element is 
    //lcm between any two numbers of the set,
        if (!(*this)(element)) {
            for (int i = 0; i < size - 1; i++) {
                for (int j = i + 1; j < size; j++) {
                    int LCM = findLCM(elements[i], elements[j]);
                    if (LCM == element) {
                        int tempSize = this->size +1;
                        int *tem = new int[tempSize];
                        for (int i = 0; i < tempSize; i++) {
                            tem[i] = elements[i]; 
                        }
                        tem[size]=element;
                        return true; // Element added
                    }
                }
            }
            return false; //not lcm
        }
        return false; //bcoz alrdy there 
    }
    // Additional Functions for functional operators
    int find(int element) const{ // Find element in the set
        for (int i =0 ; i<size ; i++){
            if(element ==elements[i]){
                return i;
            }
        }
        return -1;
    }
    int findLCM(int number1 , int number2){
        int firstPart= number1*number2;
        while (number2 != 0) {
            int temp = number2;
            number2 = number1 % number2;
            number1 = temp;
        }
        return firstPart / number1;
    }
    ~Set(){
        delete[] elements;
    };                                                           
    friend ostream &operator<<(ostream &output, const Set &val); 
    friend istream &operator>>(istream &input, Set &val);        
 };
    ostream &operator<<(ostream &output, const Set &val){
        for(int i=0 ; i<val.size ; i++){
            output<<val.elements[i]<<" ";
        }
        cout<<endl;
        return output;
    } 
    istream &operator>>(istream &input, Set &val){
        for(int i=0 ; i<val.size ; i++){
            cout<<"\nEnter Element "<<i+1<<": \t";
            input>>val.elements[i];
        }
        return input;
    }   
    void allocateArr(int *arr,int size){
        arr = new int[size];
        for(int i=0; i<size ; i++){
            arr[i]=0;
        }
    }
    void deallocate(int *arr){
        delete[] arr;
    }
 int main() {
    int* arr;
    int* arr2;
    int size = 1,size2=1;
    cout << "Enter size of set 1:\t ";
    cin >> size;
    allocateArr(arr,size);
    Set set1(arr, size);
    cin >> set1;
    cout << set1;
    cout << "Enter size of set 2:\t ";
    cin >> size2;
    allocateArr(arr2,size2);
    Set set2(arr2, size2);
    cin >> set2;
    cout << set2;
    int newElement;
    cout << "Enter a new element to add to set 1: ";
    cin >> newElement;
    if (set1(newElement,0)) cout << "Element " << newElement << " added to set 1.\n";
    cout<<set1;
    int newElementLCM;
    cout << "Enter a new element that is the LCM of any two elements in set 1: ";
    cin >> newElementLCM;
    if (set1(newElementLCM, 0, 0)) cout << "Element " << newElementLCM << " added as it's LCM \n"; 
    else cout << "Element " << newElementLCM << "is not LCM or is already in set 1.\n";
    int checkElement;
    cout << "Enter an element to check if it exists in set 1: \t";
    cin >> checkElement;
    if (set1(checkElement))cout << "\nElement " << checkElement << " exists in set 1.\n";
    else cout << "\nElement " << checkElement << " does not exist in set 1.\n";
    ////////////////////////////////////////////////////////////////////
    cout<<"\nBoth sets' union is\n";
    Set set3 = set1 + set2;
    cout<<set3;
    cout<<"\nBoth sets' intersection is\n";
    Set set4 = set1 * set2;
    cout<<set4;
    cout<<"\nBoth sets' difference is\n";
    Set set5 = set1 - set2;
    cout<<set5;
    set1 += set2;
    cout << "After union assignment in set 1 is: \n";
    cout << set1;
    set1 *= set2;
    cout << "After intersection assignment set 1 is: \n";
    cout << set1;
    set1 -= set2;
    cout << "After difference assignment set 1 is: \n";
    cout << set1;
    return 0;
}

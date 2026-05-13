#include<iostream>
using namespace std;
void sortAscending(int *p, int sizeOfArray);
void printArray(int *p, int sizeOfArray,int currentIndex);
void sortAscending(int *p, int sizeOfArray, int i, int j);
int main(){
    int size=5;
    int arr[5]={1,2,1,6,3};
    sortAscending(arr,size,0,0);
    printArray(arr,size,0);
    return 0;
}
void sortAscending(int *p, int sizeOfArray, int i, int j) {
    //base case for when we reach the end 
    if (i == sizeOfArray - 1) 
        return;

    if (j == sizeOfArray - i - 1) 
        return sortAscending(p, sizeOfArray, i + 1, 0); 
    //swapping
    if (p[j] > p[j + 1]) {
        int temp = p[j];
        p[j] = p[j + 1];
        p[j + 1] = temp;
    }

    sortAscending(p, sizeOfArray, i, j + 1); 
}
void printArray(int *p, int sizeOfArray, int currentIndex) {
    if (currentIndex == sizeOfArray) {
        cout << endl << endl;
        return;
    }
    else {
        cout << p[currentIndex] << "  ";
        printArray(p, sizeOfArray, currentIndex + 1);
    }
}

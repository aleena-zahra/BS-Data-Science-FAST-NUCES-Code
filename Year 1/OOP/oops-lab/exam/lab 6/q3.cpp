#include<iostream>
using namespace std;
void printArray(int *p, int sizeOfArray);
void printArray(int *p, int sizeOfArray, int currentIndex);
void sortNegatives(int *p, int sizeOfArray, int i, int j);
int main(){
    int size=7;
    int arr[size]={0 ,9 ,-7, 2 ,-12, 11, -20};
    sortNegatives(arr,size,0,0);
    printArray(arr,size,0);
    return 0;
}
void sortNegatives(int *p, int sizeOfArray, int i, int j) {
    if (i == sizeOfArray - 1) 
        return;

    if (j == sizeOfArray - i - 1) 
        return sortNegatives(p, sizeOfArray, i + 1, 0); 

    if (p[j] < 0) {
        int temp = p[j];
        p[j] = p[j + 1];
        p[j + 1] = temp;
    }

    sortNegatives(p, sizeOfArray, i, j + 1); // Move to next comparison
}

void printArray(int *p, int sizeOfArray, int currentIndex) {
    if (currentIndex == sizeOfArray) {
        cout << endl << endl;
        return;
    }
    
    cout << p[currentIndex] << "  ";
    printArray(p, sizeOfArray, currentIndex + 1);
}



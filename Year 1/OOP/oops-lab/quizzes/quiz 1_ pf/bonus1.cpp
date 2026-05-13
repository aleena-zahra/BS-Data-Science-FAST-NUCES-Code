#include<iostream>
using namespace std; 

void printArray(int *p, int sizeOfArray);
void inputArray(int *p, int sizeOfArray);
bool sumCombinations(int *arr, int sizeOfArray, int targetSum );
void storeCombination(int *p, int sizeOfArray,int targetSum, int startingIndex);
int main(){
    int sizeOfArray1;
    cout<<"Enter number of Elements\n";
    cin>>sizeOfArray1;
    int *arr1 = new int[sizeOfArray1]; 
    int *p1 = arr1;
    int sum;
    cout<<"Enter Target Sum to find all combinations of Elements that Add up to it\n";
    cin>>sum;
    inputArray(p1, sizeOfArray1);
    printArray(p1, sizeOfArray1);
    for(int i = 0 ; i < sizeOfArray1 ; i++){
       // combinationsOfSum(p1, sizeOfArray1, sum, i);
    }
    delete[] arr1;
    return 0;
}
/*Aleena Zahra 23i-2514 BDS-2B Assignment 1 OOP*/
#include<iostream>
using namespace std;
void allocateMemoryAndInit(int **&arr,int numberOfRows,int numberOfColumns);
void inputArray(int **arr,int numberOfRows,int numberOfColumns);
void printArray(int **arr,int numberOfRows,int numberOfColumns);
void deallocateMemory(int **arr,int numberOfRows);
void getElement(int **arr, int numberOfRows, int numberOfColumns, int row,int column);
void copyArray(int **newArr,int **arr, int newNumberOfRows, int newNumberOfColumns,int numberOfRows, int numberOfColumns);
int getSizeOfArray(int numberOfRows, int numberOfColumns);
int main(){
    int numberOfRows=0,numberOfColumns=0;
    cout<<"Enter Your Desired Number of Rows\n";
    cin>>numberOfRows;
    cout<<"Enter Your Desired Number of Columns\n";
    cin>>numberOfColumns;
    cout<<"Creating Dynamic 2D Array...\n";
    int** arr;
    allocateMemoryAndInit(arr, numberOfRows, numberOfColumns);
    inputArray(arr, numberOfRows, numberOfColumns);
    printArray(arr, numberOfRows, numberOfColumns);
    int row, column;
    cout << "Access a specific element in the matrix\n";
    cout<<"Enter row index\t";
    cin >> row;
    cout<<"\nEnter column index\t";
    cin >> column;
    getElement(arr, numberOfRows, numberOfColumns, row, column);
    cout<<"\n\nThe size of this array is "<<getSizeOfArray(numberOfRows,numberOfColumns);
    cout<<" as the array is "<<numberOfRows<<" by "<<numberOfColumns<<endl;
    cout<<"\nResize the array";
    int newNumberOfRows=0, newNumberOfColumns=0;
    cout<<"\nEnter new number of rows:\t";
    cin>>newNumberOfRows;
    cout<<"\nEnter new number of columns:\t";
    cin>>newNumberOfColumns;
    int **newArr;
    allocateMemoryAndInit(newArr,newNumberOfRows,newNumberOfColumns);
    copyArray(newArr,arr,newNumberOfRows,newNumberOfColumns,numberOfRows,numberOfColumns);
    deallocateMemory(arr, numberOfRows);
    arr = newArr;
    cout<<"\nThe new Array is: \n";
    printArray(arr,newNumberOfRows,newNumberOfColumns);
    deallocateMemory(arr, newNumberOfRows);
    return 0;

}

void allocateMemoryAndInit(int **&arr,int numberOfRows,int numberOfColumns) {
     // Dynamically allocate memory for 2D array
     arr = new int*[numberOfRows];
    for (int i = 0; i < numberOfRows; i++) {
        arr[i] = new int[numberOfColumns];
    }    
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns ; j++){
            arr[i][j]=0;
        }
    }
}
void inputArray(int **arr,int numberOfRows,int numberOfColumns) {
    int count=1;
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns ; j++){
            cout<<"\nEnter Element "<<count<<":\t";
            cin >> arr[i][j];
            count++;
        }
    }
}
void printArray(int **arr,int numberOfRows,int numberOfColumns){
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            cout << arr[i][j] << "   "; 
        }
        cout << endl;
    }
    cout<<endl<<endl;
}

void getElement(int **arr, int numberOfRows, int numberOfColumns, int row,int column){
    if(row<numberOfRows && column<numberOfColumns){
        cout << "Element at index (" << row << ", " << column << ") is " <<arr[row][column];
    }
    else{
        cout<<"Invalid Index\n";
    }
       
}
int getSizeOfArray(int numberOfRows, int numberOfColumns) {
    return numberOfRows * numberOfColumns;
}

void copyArray(int **newArr,int **arr, int newNumberOfRows, int newNumberOfColumns,int numberOfRows, int numberOfColumns){
    for(int i = 0; i < newNumberOfRows; i++) {
        for(int j = 0; j < newNumberOfColumns; j++) {
            if (i < numberOfRows && j < numberOfColumns) {
                newArr[i][j] = arr[i][j];
            } 
            else {
                //adding zeros when the size of array is bigger than before
                newArr[i][j] = 0;
            }
        }
    }
}
void deallocateMemory(int **arr, int numberOfRows) {
    for (int i = 0; i < numberOfRows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}
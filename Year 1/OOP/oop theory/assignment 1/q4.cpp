/*Aleena Zahra 23i-2514 BDS-2B Assignment 1 OOP*/
#include<iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
void allocateMemory(int ***&arr,int numberOfLayers, int numberOfRows,int numberOfColumns);
void deallocateMemory(int ***arr,int numberOfLayers,int numberOfRows);
void printArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns);
void inputArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns);
void addScalarToArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns,int scalarValue);
void multiplyScalarToArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns,int scalarValue);
void subtractScalarFromArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns,int scalarValue);
void divideScalarFromArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns,int scalarValue);
void transposeArray(int ***transposeArr,int ***arr, int numberOfLayers,int numberOfRows, int numberOfColumns);

int main(){
    
    int ***arr;
    int numberOfLayers=0,numberOfRows=0,numberOfColumns=0;
    cout<<"Enter Your Desired Number of Layers\n";
    cin>>numberOfLayers;
    cout<<"Enter Your Desired Number of Rows\n";
    cin>>numberOfRows;
    cout<<"Enter Your Desired Number of Columns\n";
    cin>>numberOfColumns;
    allocateMemory(arr,numberOfLayers,numberOfRows,numberOfColumns);
    inputArray(arr,numberOfLayers,numberOfRows,numberOfColumns);
    printArray(arr,numberOfLayers,numberOfRows,numberOfColumns);
    int scalarValue=0;
    cout<<"Enter a Scalar to Perform Arithematic Operations with to the whole Array\n";
    cin>>scalarValue;
    char userChoice;
    cout<<"Enter + to Add, - to subtract, * to multiply and / to divide the scalar with the matrix\n";
    cin>>userChoice;
    switch (userChoice)
    {
    case '+':
        addScalarToArray(arr,numberOfLayers,numberOfRows,numberOfColumns,scalarValue);
        break;
    case '-':
        subtractScalarFromArray(arr,numberOfLayers,numberOfRows,numberOfColumns,scalarValue);
        break;
    case '*':
        multiplyScalarToArray(arr,numberOfLayers,numberOfRows,numberOfColumns,scalarValue);
        break;
    case '/':
        divideScalarFromArray(arr,numberOfLayers,numberOfRows,numberOfColumns,scalarValue);
        break;    
    default:
        cout<<"No valid arithemetic operation found\n";
    }
    printArray(arr,numberOfLayers,numberOfRows,numberOfColumns);
    int ***transposeArr;
    allocateMemory(transposeArr,numberOfLayers,numberOfColumns,numberOfRows);
    transposeArray(transposeArr,arr,numberOfLayers,numberOfRows,numberOfColumns);
    deallocateMemory(arr, numberOfLayers, numberOfRows);
    arr = transposeArr;
    cout<<"\nThe Transposed Array is: \n";
    printArray(arr,numberOfLayers,numberOfColumns,numberOfRows);
    deallocateMemory(arr,numberOfLayers,numberOfRows);
    return 0;

}

void allocateMemory(int ***&arr,int numberOfLayers,int numberOfRows,int numberOfColumns){
     // Dynamically allocate memory for 3D array
    arr = new int**[numberOfLayers];
    for (int i = 0; i < numberOfLayers; ++i) {
        arr[i] = new int*[numberOfRows];
        for (int j = 0; j < numberOfRows; ++j) {
            arr[i][j] = new int[numberOfColumns];
        }
    }
}
void inputArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns){
    //seed with curent time
    srand(time(NULL));
    for(int h=0; h < numberOfLayers ; h++){
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                int randomNumber = rand() % 90 + 10;
                int randomValue = randomNumber;
                arr[h][i][j]=randomValue;
            }
        }
    }
}
void addScalarToArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns,int scalarValue){
    for(int h=0; h < numberOfLayers ; h++){
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                arr[h][i][j]+=scalarValue; 
            }
        }
    }
}
void multiplyScalarToArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns,int scalarValue){
    for(int h=0; h < numberOfLayers ; h++){
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                arr[h][i][j]*=scalarValue; 
            }
        }
    }
}
void subtractScalarFromArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns,int scalarValue){
    for(int h=0; h < numberOfLayers ; h++){
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                arr[h][i][j]-=scalarValue; 
            }
        }
    }
}
void divideScalarFromArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns,int scalarValue){
    for(int h=0; h < numberOfLayers ; h++){
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                arr[h][i][j]/=scalarValue; 
            }
        }
    }
}
void printArray(int ***arr,int numberOfLayers,int numberOfRows,int numberOfColumns){
    for(int h=0; h < numberOfLayers ; h++){
    cout<<"Layer "<<h+1<<endl<<endl;
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                cout << arr[h][i][j] << "  "; 
            }
            cout << endl;
        }
    }
}
void transposeArray(int ***transposeArr,int ***arr, int numberOfLayers,int numberOfRows, int numberOfColumns) {
    for (int l=0; l<numberOfLayers;l++){
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                //(A^T)[ j ][ i ][ k ] = (A)[ i ][ j ][ k ]
                transposeArr[i][l][j] = arr[l][i][j];
            }
        }
    }
}
void deallocateMemory(int ***arr, int numberOfLayers, int numberOfRows){
    for (int i = 0; i < numberOfLayers; i++) {
        for(int j=0; j<numberOfRows;j++){
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
    }
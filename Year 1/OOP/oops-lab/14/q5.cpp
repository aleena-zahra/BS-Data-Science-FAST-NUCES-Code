#include<iostream>
using namespace std; 
int* findLuckyNumbers(int **arr, int rowSize, int colSize);
int main(){
    int rows=3, cols=3;
    int** arr = new int*[rows];
    for(int i=0 ; i<rows ; i++){
        arr[i]= new int[cols];
    }
    int arr[rows][cols] = {{3,7,8} , {9,11,13}, {15,16,17}};
    for(int i=0 ; i<rows ; i++){
        for(int j=0 ; j<cols ; j++){
            cout<<arr[i][j]<<" ";
        }
    cout<<endl;
    }
    int* luckyNums = findLuckyNumbers(arr,rows,cols);
    cout<<"The lucky numbers in this matrix are\n";
    for(int i=0 ; i<rows ; i++){
        cout<<luckyNums[i]<<" ";
    }
    return 0;
}

int* findLuckyNumbers(int **arr, int rowSize, int colSize){
    
    for(int i =0 ; i<rowSize ; i++){
        int minimum = arr[i][0];
        int maximum = arr[i][0];
        for(int j=0 ; j<colSize ; j++){
            if(arr[i][j]<minimum){
                minimum= arr[i][j];
            }
        }
    }
}
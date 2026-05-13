#include<iostream>
#include<cmath>
using namespace std;
void allocateMemory(char **&arr, int numberOfRows, int numberOfColumns);
void deallocateMemory(char **arr, int numberOfRows);
void initializeArray(char **arr,int numberOfRows,int numberOfColumns);
void printGrid(char **arr, int n);
bool rowIsValid(char **arr , int n , int row);
bool columnIsValid(char **arr , int n, int column);
bool diagonalIsValid(char **arr , int n,  int row , int column);
bool solveStars(char **arr,int n, int columnIndex=0,int count=0);
int main(){
    cout<<" This program displays valid positions of n number of stars in a n by n grid\n";
    cout<<" Valid positions are when no star is in the same row, column or diagonal as the others.\n";
    cout<<" Enter n:\t";
    int n;
    cin>>n;
    char **arr;
    allocateMemory(arr,n,n);
    initializeArray(arr,n,n);
    bool solutionExists = solveStars(arr,n,0,0);
    if(!solutionExists){
        cout<<"\nSolution for "<<n<<" not found :(";
    }
    else{
        printGrid(arr,n);
    }
    deallocateMemory(arr,n);
    return 0;
}
bool solveStars(char **arr,int n, int columnIndex,int count){
    if(columnIndex>=n){
        cout<<"\nThe number of stars in the grid are "<<count<<endl;
        return true;
    }
    for (int i = 0; i < n; i++) {
        if((columnIsValid(arr,n,columnIndex)&&diagonalIsValid(arr,n,i,columnIndex)&&rowIsValid(arr,n,i))){
            arr[i][columnIndex]='*';
            count++;
            if(solveStars(arr,n,++columnIndex,count)){
                return true;
            }
            else{
                arr[i][--columnIndex]=' ';
                count--;
            }
        }
    }
    return false;}


void allocateMemory(char **&arr,int numberOfRows,int numberOfColumns){
    arr = new char*[numberOfRows];
    for (int i = 0; i < numberOfRows; i++) {
        arr[i] = new char[numberOfColumns];
    }    
}
void deallocateMemory(char **arr, int numberOfRows){
    for (int i = 0; i < numberOfRows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    }
void initializeArray(char **arr,int numberOfRows,int numberOfColumns){
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            arr[i][j] = ' '; 
        }
    }
}
void printGrid(char **arr, int n) {
    for (int j = 0; j < n; j++) {
            cout << "+---";
        }
        cout << "+" << endl;
     for (int i = 0; i < n; i++) {
        
        for (int j = 0; j < n; j++) {
            cout << (arr[i][j] == '*' ? "| * " : "|   ");
        }
        cout << "|" << endl;

        for (int j = 0; j < n; j++) {
            cout << "+---";
        }
        cout << "+" << endl;
    }
}

void printArr(char **arr, int numberOfRows,int numberOfColumns ){
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            cout<< arr[i][j]<<" "; 
        }
        cout<<endl;
    }
}
bool rowIsValid(char **arr ,int n, int row){
    for(int j = 0 ; j<n ; j++){
        if(arr[row][j]=='*'){
            return false;
        }
    }
    return true;
}
bool columnIsValid(char **arr , int n,int column){
    for(int i = 0 ; i<n ; i++){
        if(arr[i][column]=='*'){
            return false;
        }
    }
    return true;
}
bool diagonalIsValid(char **arr , int n ,int row, int column){
   for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { 
            if (arr[i][j] == '*' && abs(i - row) == abs(j - column))
                return false;
        }
    }
    return true;
}

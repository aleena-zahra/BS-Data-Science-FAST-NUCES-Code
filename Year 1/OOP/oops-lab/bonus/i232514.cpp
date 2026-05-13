#include<iostream>
#include<random>
using namespace std;
void allocateMemory(char **&arr, int numberOfRows, int numberOfColumns);
void deallocateMemory(char **arr, int numberOfRows);
void initializeArray(char **arr,int numberOfRows,int numberOfColumns);
void printArr(char **arr, int numberOfRows,int numberOfColumns );
void printGrid(char **arr, int n);
void printStar();
bool rowIsValid(char **arr , int n , int row);
bool columnIsValid(char **arr , int n, int column);
bool diagonalIsValid(char **arr , int n,  int row , int column);

int main(){
    srand(time(nullptr));
    //input n
    cout<<" This program displays valid positions of n number of stars in a n by n grid\n";
    cout<<" Valid positions are when no star is in the same row, column or diagonal as the others.\n";
    cout<<" Enter n:\t";
    int n;
    cin>>n;
    //allocate memory n by n matrix
    char **arr;
    allocateMemory(arr,n,n);
    //initialize the arr as spaces
    initializeArray(arr,n,n);
    //randomly generate one aesterisk
    int row = rand() % n;
    int col = rand() % n;
    arr[row][col]='*';
    //printArr(arr,n,n);
    //count for valid stars(one already placed on grid)
    int count=1; 
    //check for the others' placement on loop of n-1
    while(count!=n){
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(arr[i][j]==' '){
                    if(rowIsValid(arr,n,i) && columnIsValid(arr,n,j) && diagonalIsValid(arr,n,i,j)){
                        arr[i][j]='*';
                        count++;
                    }
                }
            }
        }
        if(count!=n){
            initializeArray(arr,n,n);
            //randomly generate one aesterisk
            int row = rand() % n;
            int col = rand() % n;
            arr[row][col]='*';
            count=1;
        }
    }
    cout<< "valid number of stars are "<<count<<endl;
    printGrid(arr, n);
    //deallocate memory 
    deallocateMemory(arr,n);
    return 0;
}
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
            //if theres a filled index and the length of col and row is the same then its in diagonal. so invalid
            if (arr[i][j] == '*' && abs(i - row) == abs(j - column))
                return false;
        }
    }
    return true;
}
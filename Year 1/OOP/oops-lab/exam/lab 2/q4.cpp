#include<iostream>
using namespace std;
void printArray(int ***arr, int layers ,int numberOfRows, int numberOfColumns );
void inputArray(int ***arr, int layers , int numberOfRows, int numberOfColumns );
void sumOfAllElements(int ***arr, int layers , int numberOfRows, int numberOfColumns );
void sumOfRows(int ***arr, int layers , int numberOfRows, int numberOfColumns );
void sumOfColumns(int ***arr, int layers , int numberOfRows, int numberOfColumns );
void sumOfLayers(int ***arr, int layers , int numberOfRows, int numberOfColumns ); 
void deallocateMemory(int ***arr, int layers , int numberOfRows, int numberOfColumns );
int main() {
 int numberOfRows, numberOfColumns, layers;
    cout<<"Enter number of Layers\n";
    cin>>layers;
    cout<<"Enter number of Rows\n";
    cin>>numberOfRows;
    cout<<"Enter number of Columns\n";
    cin>>numberOfColumns;
    int*** arr = new int**[layers];
    for (int i = 0; i < layers; ++i) {
        arr[i] = new int*[numberOfRows];
        for (int j = 0; j < numberOfRows; ++j) {
            arr[i][j] = new int[numberOfColumns];
        }
    }
    inputArray(arr, layers,numberOfRows, numberOfColumns);
    cout << "Initially the array is:" << endl;
    printArray(arr, layers, numberOfRows, numberOfColumns);
    sumOfAllElements(arr, layers, numberOfRows, numberOfColumns);
    sumOfLayers(arr, layers, numberOfRows, numberOfColumns);
    sumOfRows(arr, layers, numberOfRows, numberOfColumns);
    sumOfColumns(arr, layers, numberOfRows, numberOfColumns);
    deallocateMemory(arr, layers, numberOfRows, numberOfColumns);
    return 0;
}
void inputArray(int ***arr, int layers , int numberOfRows, int numberOfColumns ){
    cout<<"Enter Elements of the 3D Array\n";
    for(int h = 0; h < layers; h++) {
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                cin >> arr[h][i][j]; // Assign the address of each row to the 3D pointer
            }
        }
    }
}
void printArray(int ***arr, int layers , int numberOfRows, int numberOfColumns ){
    for(int h = 0; h < layers; h++) {
        cout<<"Layer "<<h+1<<endl;
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                cout<< arr[h][i][j]<<" "; // Assign the address of each row to the 3D pointer
            }
            cout<<endl;
        }
    }
}
void sumOfAllElements(int ***arr, int layers , int numberOfRows, int numberOfColumns ){
    int sum=0;
    for(int h = 0; h < layers; h++) {
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                sum+= arr[h][i][j]; 
            }
        }
    }
    cout<<"\nThe sum of all elements in the 3D Array is "<<sum;
}
void sumOfRows(int ***arr, int layers , int numberOfRows, int numberOfColumns ){
    for(int h = 0; h < layers; h++) {
        cout<<"\nIn layer "<<h+1;
        for(int i = 0; i < numberOfRows; i++) {
            int sum=0;
            for(int j = 0; j < numberOfColumns; j++) {
                sum+= arr[h][i][j]; 
            }
            cout<<"\nThe sum of all elements in Row "<<i+1<<" is "<<sum;
        }
    }
}
void sumOfColumns(int ***arr, int layers , int numberOfRows, int numberOfColumns ){
    for(int h = 0; h < layers; h++) {
        cout<<"\nIn layer "<<h+1;
        for(int i = 0; i < numberOfColumns; i++) {
            int sum=0;
            for(int j = 0; j < numberOfRows; j++) {
                sum+= arr[h][j][i]; 
            }
            cout<<"\nThe sum of all elements in Column "<<i+1<<" is "<<sum;
        }
    }
}
void sumOfLayers(int ***arr, int layers , int numberOfRows, int numberOfColumns ){
    for(int h = 0; h < layers; h++) {
        int sum=0;
        for(int i = 0; i < numberOfRows; i++) {
            for(int j = 0; j < numberOfColumns; j++) {
                sum+= arr[h][i][j]; 
            }
        }
        cout<<"\nThe sum of all elements in Layer " <<h+1<<" is "<<sum;
    }
}
void deallocateMemory(int ***arr, int layers , int numberOfRows, int numberOfColumns ){
    for (int i = 0; i < layers; ++i) {
        for (int j = 0; j < numberOfRows; ++j) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
}
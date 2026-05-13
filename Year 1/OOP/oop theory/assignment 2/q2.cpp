#include<iostream>
using namespace std;

void deallocateMemory(int** &arr, int numberOfRows, int index);
void allocateMemory(int** &arr, int numberOfRows, int numberOfColumns, int index);
void inputArray(int **arr, int arrHeight, int arrWidth, int i, int j);
void printArray(int **arr, int arrHeight, int arrWidth, int i, int j);

//void calculateNextState(int **arr, int **newArr, int arrHeight, int arrWidth, int i, int j);
void conwaysGameOfLife(int **arr, int **newArr, int arrHeight, int arrWidth, int i, int j);
void calculateNextState(int **arr, int **newArr, int arrHeight, int arrWidth, int i, int j,int a=-1,int b=-1) {
    int state = arr[i][j];
    int neighbourAliveCount = 0;
    if (a <= 1 ) {
        if (b <= 1) {
            if (!(a == 0 && b == 0)) {
               // cout<<"a is"<<a<<" b is "<<b<<" and index is "<<arr[i][j]<<endl;
                if (i + a >= 0 && i + a < arrHeight && j + b >= 0 && j + b < arrWidth) {
                // Increment the count if the neighboring cell is alive
                neighbourAliveCount += arr[i][j];
                }
            }
        calculateNextState(arr, newArr, arrHeight, arrWidth, i, j,a,++b);
        }
        calculateNextState(arr, newArr, arrHeight, arrWidth, i, j,++a,-1);
    }
    //cout<<"neighbours alive are "<<neighbourAliveCount<<endl;

    if (state == 1) {
        if (neighbourAliveCount > 3 || neighbourAliveCount < 2)
            newArr[i][j] = 0;
        else
            newArr[i][j] = 1;
    } 
    else if (state == 0) {
        if (neighbourAliveCount == 3)
            newArr[i][j] = 1;
        else
            newArr[i][j] = 0;
    }
}
int main() {
    int arrHeight, arrWidth;
    
    cout << "Enter number of rows: ";
    cin >> arrHeight;
    cout << "Enter number of columns: ";
    cin >> arrWidth;
    
    int **arr, **newArr;
    allocateMemory(arr, arrHeight, arrWidth,0);
    allocateMemory(newArr, arrHeight, arrWidth,0);
    
    cout << "Enter elements of arr. Each cell can be either alive (1) or dead (0):" << endl;
    inputArray(arr, arrHeight, arrWidth, 0, 0);

    cout << "Initial state of arr of Conway's Game of Life:" << endl;
    printArray(arr, arrHeight, arrWidth, 0, 0);

    conwaysGameOfLife(arr, newArr, arrHeight, arrWidth, 0, 0);

    cout << "Next state of arr of Conway's Game of Life:" << endl;
    printArray(newArr, arrHeight, arrWidth, 0, 0);

    deallocateMemory(arr, arrHeight,0);
    deallocateMemory(newArr, arrHeight,0);
    return 0;
}



void inputArray(int **arr, int arrHeight, int arrWidth, int i, int j) {
    if (i == arrHeight)
        return;
    if (j == arrWidth) {
        inputArray(arr, arrHeight, arrWidth, i + 1, 0);
        return;
    }
    cin >> arr[i][j];
    inputArray(arr, arrHeight, arrWidth, i, j + 1);
}

void printArray(int **arr, int arrHeight, int arrWidth, int i, int j) {
    if (i == arrHeight)
        return;
    if (j == arrWidth) {
        cout << endl;
        printArray(arr, arrHeight, arrWidth, i + 1, 0);
        return;
    }
    cout << arr[i][j] << " ";
    printArray(arr, arrHeight, arrWidth, i, j + 1);
}

void conwaysGameOfLife(int **arr, int **newArr, int arrHeight, int arrWidth, int i, int j) {
    if (i == arrHeight)
        return;
    if (j == arrWidth) {
        conwaysGameOfLife(arr, newArr, arrHeight, arrWidth, i + 1, 0);
        return;
    }
    calculateNextState(arr, newArr, arrHeight, arrWidth, i, j);
    conwaysGameOfLife(arr, newArr, arrHeight, arrWidth, i, j + 1);
}



void allocateMemory(int** &arr, int numberOfRows, int numberOfColumns, int index) {
    if (index < numberOfRows) {
        arr[index] = new int[numberOfColumns];
        allocateMemory(arr, numberOfRows, numberOfColumns, index + 1);
    }
}

void deallocateMemory(int** &arr, int numberOfRows, int index) {
    if (index < numberOfRows) {
        delete[] arr[index];
        arr[index] = nullptr;
        deallocateMemory(arr, numberOfRows, index + 1);
    }
}

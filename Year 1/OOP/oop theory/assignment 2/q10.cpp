//Aleena Zahra 23i-2514 BDS-2B OOP ASSIGNMENT 2
#include <iostream>
using namespace std;
int calculateHourglassSum(int **arr, int row, int col);
int maxHourGlass(int **arr, int row, int col, int maxSum, int numberOfRows, int numberOfColumns);
void deallocateMemory(int** &arr, int numberOfRows, int index);
void allocateMemory(int** &arr, int numberOfRows, int numberOfColumns, int index);
void inputArray(int **arr, int numberOfRows, int numberOfColumns, int index, int totalElements);
int main() {
    int numberOfRows = 6; 
    int numberOfColumns = 6;
    int** arr = new int*[numberOfRows];
    allocateMemory(arr, numberOfRows, numberOfColumns, 0);
    cout << "Enter the elements of the array: \n";
    inputArray(arr, numberOfRows, numberOfColumns, 0, numberOfRows * numberOfColumns);
    int maxSum = maxHourGlass(arr, 0, 0, -1000, numberOfRows, numberOfColumns);
    cout << "The maximum hourglass sum is: " << maxSum << endl;
    deallocateMemory(arr, numberOfRows, 0);

    return 0;
}

int calculateHourglassSum(int **arr, int row, int col) {
    return arr[row][col] + arr[row][col + 1] + arr[row][col + 2] +
           arr[row + 1][col + 1] +
           arr[row + 2][col] + arr[row + 2][col + 1] + arr[row + 2][col + 2];
}

int maxHourGlass(int **arr, int row, int col, int maxSum, int numberOfRows, int numberOfColumns) {
    // if we've reached beyond the array bounds return the maximum sum found so far
    if (row >= numberOfRows - 2 || col >= numberOfColumns - 2) {
        return maxSum;
    }
    int currentSum = calculateHourglassSum(arr, row, col);
    if (currentSum > maxSum) {
        maxSum = currentSum;
    }
    if (col < numberOfColumns - 3) {
        return maxHourGlass(arr, row, col + 1, maxSum, numberOfRows, numberOfColumns);
    } else {
        return maxHourGlass(arr, row + 1, 0, maxSum, numberOfRows, numberOfColumns);
    }
}



void inputArray(int **arr, int numberOfRows, int numberOfColumns, int index, int totalElements) {
    if (index < totalElements) {
        cout<<"Enter Element:\t";
        cin >> arr[index / numberOfColumns][index % numberOfColumns];
        inputArray(arr, numberOfRows, numberOfColumns, index + 1, totalElements);
    }
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





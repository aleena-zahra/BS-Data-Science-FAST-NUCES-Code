#include<iostream>
using namespace std;

void printArray(int **arr, int numberOfRows, int numberOfColumns );
void inputArray(int **arr,  int numberOfRows, int numberOfColumns ); 
int calculateHourglassSum(int **arr, int row, int col ); 
int main() {
    int numberOfRows, numberOfColumns;
    cout<<"Enter number of Rows\n";
    cin>>numberOfRows;
    cout<<"Enter number of Columns\n";
    cin>>numberOfColumns;
    int** arr = new int*[numberOfRows];
    for (int i = 0; i < numberOfRows; i++) {
        arr[i] = new int[numberOfColumns];
    }    
    inputArray(arr,numberOfRows, numberOfColumns);
    cout << "Initially the array is:" << endl;
    printArray(arr, numberOfRows, numberOfColumns);
    // Iterate through each hourglass to find the maximum hourglass sum
    int sum = 0;
    int maxSum=-10000;
    for (int i = 0; i < numberOfRows - 2; i++) { //index 3 is max when total rows are 6
        for (int j = 0; j < numberOfColumns - 2; j++) { //index 3 is max when total columns are 6
            //checking all hourglass sums in loop
            int sum = calculateHourglassSum(arr, i, j);
            if (sum > maxSum) {
                maxSum = sum;
            }
        }
    }

    cout << "The hourglass sum that is the largest is " << maxSum << endl;
     // Deallocate memory for 2D array
    for (int i = 0; i < numberOfRows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}
void inputArray(int **arr,  int numberOfRows, int numberOfColumns ){
    cout<<"Enter Elements of Array: \n";
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            cin >> arr[i][j]; 
        }
    }
}
void printArray(int **arr,  int numberOfRows, int numberOfColumns ){
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            cout<< arr[i][j]<<" "; 
        }
        cout<<endl;
    }
}
int calculateHourglassSum(int **arr, int row, int col) {
    int sum = arr[row][col] + arr[row][col + 1] + arr[row][col + 2]; //top row elements
    sum += arr[row + 1][col + 1]; // Middle row element
    sum += arr[row + 2][col] + arr[row + 2][col + 1] + arr[row + 2][col + 2]; //bottom row elements
    return sum;
}
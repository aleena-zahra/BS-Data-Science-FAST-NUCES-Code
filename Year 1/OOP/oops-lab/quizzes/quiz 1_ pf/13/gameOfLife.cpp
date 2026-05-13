#include<iostream>
using namespace std;

void printArray(int **p, int numberOfRows, int numberOfColumns); 
void inputArray(int **p, int numberOfRows, int numberOfColumns); 
void reproduction(int **p, int numberOfRows, int numberOfColumns); 
void underpopulation(int **p, int numberOfRows, int numberOfColumns);
void overpopulation(int **p, int numberOfRows, int numberOfColumns);
void notLonely(int **p, int numberOfRows, int numberOfColumns);

int main() {
    int numberOfRows, numberOfColumns;
    cout<<"Enter number of Rows\n";
    cin>>numberOfRows;
    cout<<"Enter number of Columns\n";
    cin>>numberOfColumns;
    int arr[numberOfRows][numberOfColumns];
    int **p = new int*[numberOfRows]; // 2D pointer

    for(int i = 0; i < numberOfRows; i++) {
        p[i] = arr[i]; // Assign the address of each row to the 2D pointer
    }

    inputArray(p, numberOfRows, numberOfColumns);
    cout << "Initially the array is:" << endl;
    printArray(p, numberOfRows, numberOfColumns);
    reproduction(p, numberOfRows, numberOfColumns);
   
    delete[] p; 

    return 0;
}

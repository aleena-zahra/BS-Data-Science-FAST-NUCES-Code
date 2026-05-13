
#include<iostream>
using namespace std;

void printArray(int **p, int numberOfRows, int numberOfColumns); 
void inputArray(int **p, int numberOfRows, int numberOfColumns); 
void transposeArray(int **p, int numberOfRows, int numberOfColumns); 
void backwardsRowsArray(int **p, int numberOfRows, int numberOfColumns); 
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
    transposeArray(p, numberOfRows, numberOfColumns);
    printArray(p, numberOfRows, numberOfColumns);
    backwardsRowsArray(p, numberOfRows, numberOfColumns);
    cout << "After rotation the array is:\n\n";
    printArray(p, numberOfRows, numberOfColumns);
    delete[] p; 

    return 0;
}

void printArray(int **p, int numberOfRows, int numberOfColumns) {
    
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            // Access elements using 2D pointer
            cout << p[i][j] << "  "; 
        }
        cout << endl;
    }
    cout<<endl<<endl;
}
void inputArray(int **p, int numberOfRows, int numberOfColumns) {
    int number=0;
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            number++;
            p[i][j] = number;
        }
    }
}
void transposeArray(int **p, int numberOfRows, int numberOfColumns) {
    int temp=0;
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = i; j < numberOfColumns; j++) {
            int temp = p[i][j];
            p[i][j] = p[j][i];
            p[j][i] = temp;
        }
    }
}
void backwardsRowsArray(int **p, int numberOfRows, int numberOfColumns) {
    int lastRowPosition= numberOfRows-1;
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns/2; j++) {
            int temp = p[i][j];
            p[i][j] = p[i][lastRowPosition-j];
            p[i][lastRowPosition-j] = temp;
        }
        
    }
}
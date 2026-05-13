#include<iostream>
using namespace std;

void printArray(int *p, int sizeOfArray);
void inputArray(int *p, int sizeOfArray); 
void sortAscending(int *p, int sizeOfArray);
void sortDescending(int *p, int sizeOfArray);
void mergeArrays(int *p1,int *p2,int *p3, int sizeOfArray1, int sizeOfArray2);
int main() {
    int sizeOfArray1;
    cout<<"FIRST ARRAY\n";
    cout<<"Enter number of Elements\n";
    cin>>sizeOfArray1;
    int *arr1 = new int[sizeOfArray1]; 
    int *p1 = arr1;

    inputArray(p1, sizeOfArray1);
    sortAscending(p1, sizeOfArray1);
    printArray(p1, sizeOfArray1);

    int sizeOfArray2;
    cout<<"SECOND ARRAY\n";
    cout<<"Enter number of Elements\n";
    cin>>sizeOfArray2;
    int *arr2 = new int[sizeOfArray2]; 
    int *p2 = arr2;

    inputArray(p2, sizeOfArray2);
    sortDescending(p2, sizeOfArray2);
    printArray(p2, sizeOfArray2);

    int sizeOfArr3 = sizeOfArray1 + sizeOfArray2;
    int *arr3 = new int[sizeOfArr3]; 
    int *p3 = arr3;
    mergeArrays(p1,p2,p3,sizeOfArray1,sizeOfArray2);
    printArray(p3,sizeOfArr3);
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    return 0;
}
void printArray(int *p, int sizeOfArray) {
    
    for(int i = 0; i < sizeOfArray; i++) {
            // Access elements using pointer
            cout << p[i] << "  "; 
    }
    cout<<endl<<endl;
}
void inputArray(int *p, int sizeOfArray) {
    
    for(int i = 0; i < sizeOfArray; i++) {
            cout<<"Enter Element "<<i+1<<":\t";
             // Access elements using pointer
            cin >> p[i];
            cout<<endl;
        
    }
}
void sortAscending(int *p, int sizeOfArray){
    for(int i =0 ; i<sizeOfArray-1 ;i++){
        for(int j=0; j<sizeOfArray-i-1 ; j++){
            if(p[j]>p[j+1]){
                int temp = p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}
void sortDescending(int *p, int sizeOfArray){
    for (int i = 0; i < sizeOfArray - 1; i++) {
        for (int j = 0; j < sizeOfArray - i - 1; j++) {
            if (p[j] < p[j + 1]) {
                int temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
void mergeArrays(int *p1, int *p2, int *p3, int sizeOfArray1, int sizeOfArray2) {
    int sizeOfArr3 = sizeOfArray1 + sizeOfArray2;
    int i = 0, j = 0,k=0, index = 0;
    
    while (index < sizeOfArr3) {
        int num1 = 2000, num2 = 2000;

        // Find the smallest number in array 1
        for (int a = 0; a < sizeOfArray1; a++) {
            if (p1[a] <= num1) {
                num1 = p1[a];
                // store index of nua1 
                j = a; 
            }
        }

        // Find the smallest number in the second array
        for (int n = 0; n < sizeOfArray2; n++) {
            if (p2[n] <= num2) {
                num2 = p2[n];
                // store index of num2 
                k = n; 
            }
        }
        //whichever of these is the smallest that will be the number merged in array 3
        if (num1 <= num2) {
            p3[index] = num1;
            p1[j] = 1001; 
            index++;
        } else {
            p3[index] = num2;
            p2[k] = 1001; 
            index++;
        }
    }
}


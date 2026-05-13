#include<iostream>
using namespace std;

void printArray(int *p, int sizeOfArray);
void inputArray(int *p, int sizeOfArray); 
void mixArrays( int arr1[],int arr2[],int sizeOfArray1, int sizeOfArray2);
int main() {
    int sizeOfArray1;
    cout<<"FIRST ARRAY\n";
    cout<<"Enter number of Elements\n";
    cin>>sizeOfArray1;
    int *arr1 = new int[sizeOfArray1]; 
    int *p1 = arr1;
    inputArray(p1, sizeOfArray1);
    printArray(p1, sizeOfArray1);
    int sizeOfArray2;
    cout<<"\nSECOND ARRAY\n";
    cout<<"Enter number of Elements\n";
    cin>>sizeOfArray2;
    int *arr2 = new int[sizeOfArray2]; 
    int *p2 = arr2;
    inputArray(p2, sizeOfArray2);
    printArray(p2, sizeOfArray2);
    mixArrays(arr1,arr2,sizeOfArray1,sizeOfArray2);

    // Deallocate memory
    delete[] arr1;
    delete[] arr2;
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
void mixArrays(int arr1[],int arr2[], int sizeOfArray1, int sizeOfArray2){
    int sizeOfArray3 = sizeOfArray1+sizeOfArray2 , count=0;
    int arr3[sizeOfArray3];
    int last=sizeOfArray3-1;
        for (int j = 0; j < sizeOfArray2; j++){
            if (arr1[j]%2==0){//even
                arr3[count++]=arr1[j];
            }
            else
                arr3[last--]=arr1[j];
        }
        for (int j = 0; j < sizeOfArray2; j++){
            if (arr2[j]%2==0){//even
                arr3[count++]=arr2[j];
            }
            else
                arr3[last--]=arr2[j];
            
        }
        
    
    for(int i = 0; i < sizeOfArray3; i++) {
            cout << arr3[i] << "  "; 
    }
    
}
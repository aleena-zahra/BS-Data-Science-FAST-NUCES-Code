#include<iostream>
#include<string>
using namespace std;

void printArray(int *p, int sizeOfArray);
void inputArray(int *p, int sizeOfArray); 
void combinationsOfSum(int *p, int sizeOfArray,int targetSum, int startingIndex);
int numberOfZeros(int *p, int sizeOfArray);
int main() {
    int sizeOfArray1;
    cout<<"Enter number of Elements\n";
    cin>>sizeOfArray1;
    int *arr1 = new int[sizeOfArray1]; 
    int *p1 = arr1;
    int sum;
    cout<<"Enter Target Sum to find all combinations of Elements that Add up to it\n";
    cin>>sum;
    inputArray(p1, sizeOfArray1);
    printArray(p1, sizeOfArray1);
    for(int i = 0 ; i < sizeOfArray1 ; i++){
        combinationsOfSum(p1, sizeOfArray1, sum, i);
    }
    delete[] arr1;
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
void combinationsOfSum(int *p, int sizeOfArray, int targetSum, int startingIndex) {
    int currentSum = 0;
    //max lenght would be if all elements were valid 
    int str[sizeOfArray] = {0};
    int j=0;
    int index = startingIndex;
    do{ 
        if(p[index] != 0){
            //Access elements using pointer
            currentSum += p[index];
            str[j] = p[index];
            j++;
            p[index];
            if(currentSum >targetSum){
                //combinationsOfSum(p,sizeOfArray,targetSum,index+1);
                currentSum -=p[index];
                j--;
            }
        }

        if(index==sizeOfArray-1){
            index=-1;
            
        }
        index++;
    }while(index != startingIndex && currentSum!= targetSum);
    
    
    //-14 -6-1 0 7 14 14 
    if(currentSum == targetSum){
        int i=0;
        while(str[i] != 0){
            cout << " "<<str[i] ;
            i++;
        }
        cout<<endl;
        int zeroCount=numberOfZeros(p,sizeOfArray);
        for(int j=0; j<=zeroCount ;j++){
            int i=0;
            while(str[i] != 0){
                cout << " "<<str[i] ;
                i++;
            }
                cout<< " 0\n";
                
        }
    }
    
}
    
    

int numberOfZeros(int *p, int sizeOfArray){
    int count=-1;
    for(int i=0; i<sizeOfArray ; i++){
        if(p[i] == 0){
            count++;
        }
    }
    return count;

}
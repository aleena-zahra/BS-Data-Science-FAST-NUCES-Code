#include<iostream>
using namespace std;
    void swapfunction(int *num1,int *num2){
    int newNumber;
    newNumber = *num1;
    *num1 = *num2;
    *num2 = newNumber; 
    }
    int main(){
    int num1;
    int num2;
    cout<<"Enter Number 1\n";
    cin>>num1;
    cout<<"Enter Number 2\n";
    cin>>num2;
    
    swapfunction(&num1,&num2);
    cout<<"swapped values are "<<num1<<" and "<<num2;
    return 0;
    
    }

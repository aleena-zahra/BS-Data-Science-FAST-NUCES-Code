#include<iostream>
using namespace std;

    int main(){
    
    int tableOfTwo[12];
    int *pntr = tableOfTwo;
    for(int i=0 ; i < 12 ; i++){
    tableOfTwo[i]= 2* (i+1);
    }
    for(int i=0 ; i < 12 ; i++){
    cout<<*(pntr+i)<<" ";
    }
    
    return 0;
    
    }

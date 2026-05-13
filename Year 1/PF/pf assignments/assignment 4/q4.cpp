/*
Aleena Zahra 
23i-2514 
BDS-B 
Assignment #4
*/ 
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
   int main(){
    srand(time(0));
    int a[60], sumofValues[60];
    int i,j,profitRightNow,maximumProfit=-20000,startValue,endValue;

    cout<<"The array is:\n";
    for(i=0;i<60;i++){
      a[i] = (rand()%21)-10;
      cout<<a[i]<<" ";
    }
    

    for ( i = 0; i < 60; ++i) {
        profitRightNow +=a[i];


    if (maximumProfit < profitRightNow){
            maximumProfit = profitRightNow;
            startValue = j;
            endValue = i;
    }
 
        if (profitRightNow < 0){
            profitRightNow = 0;
            j=i+1;
        }
    }

    cout<<"\nThe Maximum Profit is "<<maximumProfit<<"\nThe Start Index is "<<startValue<<" and the End Index is "<<endValue<<endl;
    cout<<"The number at starting index is "<<a[startValue];
    cout<<endl<<"The number at ending index is "<<a[endValue];
    int sum=0;
    for(int i=startValue;i<=endValue;i++){
        sum += a[i];
        
    }
    cout<<endl<<"The sum of the subarray (should be equal to maximum profit) from the starting to ending value is "<<sum;

    return 0;
   }
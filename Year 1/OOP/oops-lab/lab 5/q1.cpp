#include<iostream>
using namespace std;
int factorial(int x){
    if(x<0){
        return -1;
    }
    if (x==1 || x==0){
        return 1;
    }
    else return x*factorial(x-1);
}
#include<iostream>
using namespace std;
int main(){
int a = 21220;
//covert to array;
int arr[5] = {2,2,0};

}

void fun(int *arr,int position,int digit){
    if(digit<0){
        return;
    }
    if(arr[position]==1 && digit){
        cout<<"One";
    }
    else if(arr[position]==2){
        cout<<"Two";
    }
    //check position
    if(digit==2){
        cout<<"Hundred";
    }
    if(digit==1){

    }
    fun(arr+1,position+1,digit);
}



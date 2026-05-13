#include<iostream>
using namespace std;
bool isMember(int *arr, int length,int num,int count=0){
    if(count!=length){
        if(arr[count]==num){
            return true;
        }
        else
        isMember(arr,5,num,count+1);
    }
    else{
        return false;
    }
}
 int main(){
    int arr[5]={1,2,3,4,5};
    int num;
    cout<<"Enter num to find in array\n";
    cin>>num;
    if(isMember(arr,5,num,0)==true){
        cout<<num<<" is a member of array \n";
    }
    else{
        cout<<num<<" is NOT a member of array \n";
    }
 }
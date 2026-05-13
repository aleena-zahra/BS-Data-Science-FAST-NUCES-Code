#include<iostream>
using namespace std;
int binarySearch(int *arr ,int target, int start , int end){
    if(start >=end){
        cout<<"\nnot found";
        return -1;
    }
    int middle = (start + end) / 2;
    if(target == arr[middle] ){
        return middle;
    }
    else if(target > arr[middle]){
        binarySearch(arr,target,middle+1,end);
    }
    else if(target < arr[middle]){
        binarySearch(arr,target,start,middle);
    }
}
int main(){
    int *arr= new int[10];
    int count=1;
    for(int i =0 ; i<10 ; i++){
        arr[i] = count++;
    }
    for(int i =0 ; i<10 ; i++){
        cout<< arr[i] << " ";
    }
    int numToFind=0;
    cout<<"\nEnter num to find:\t";
    cin>>numToFind;
    cout<<"The index is "<<binarySearch(arr,numToFind,0,10);
    return 0;
}
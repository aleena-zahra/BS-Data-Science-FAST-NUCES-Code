#include<iostream>
using namespace std;

void maxHeap(int *a,int m, int n){
    int j,t;
    t = a[m];
    j = 2*m;
    while(j<=n){
        if(j<n && a[j+1] > a[j])
        j++;
        if(t>a[j])
        break;
        else if(t<=a[j]){
            a[j/2]=a[j];
            j=2*j;
        }
    }
}
int main(){
    int size=5;
    int arr[size];
    for (int i =0 ; i<size; i++){
        cout<<"\nenter element "<<i+1;
        cin>>arr[i];
    }
    for (int i =0 ; i<size; i++){
        cout<<arr[i];
    }

    for (int i =0 ; i<size; i++){
        cout<<arr[i];
    }
    return 0;
}
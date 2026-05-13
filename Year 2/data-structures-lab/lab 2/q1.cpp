#include<iostream>
using namespace std;

template <typename T> bool compareValues(const T& a, const T& b){
    
    return a==b;
}

int main() {
    int num1=1,num2=1;
    float num3=3.2,num4=4.4;
    char num5='n',num6='n';
    cout<<"\nComparing both ints: "<<compareValues(num1,num2);
    cout<<"\nComparing both floats: "<<compareValues(num3,num4);
    cout<<"\nComparing both chars: "<<compareValues(num5,num6);
    return 0;
}
#include<iostream>
using namespace std;

int main (){

int n1,n2=0;
cout<<"Enter the first number"<<endl;
cin>>n1;
cout<<"Enter the second number"<<endl;
cin>>n2;

if(n1==n2)
cout<<"Both numbers are equal";
else if (n1 > n2)
cout<< "The first number is greater than the second number";
else if (n2>n1)
cout<<"The second number is greater than the first number";

return 0;
}


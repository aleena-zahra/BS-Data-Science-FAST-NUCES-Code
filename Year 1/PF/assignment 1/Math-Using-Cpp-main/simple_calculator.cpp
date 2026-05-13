#include<iostream>
using namespace std;

int main(){
int num1, num2;
char oper;
//oper is the operator like multiplication, addition etc
cout<<"Enter number 1  ";
cin>>num1;

cout<<"Enter number 2  ";
cin>>num2;

cout<<"Enter operator  ";
cin>>oper;

if(oper=='+')
cout<< num1+num2;

if(oper=='-')
cout<< num1-num2;

if(oper=='*')
cout<< num1*num2;

if(oper=='/')
cout<< num1/num2;

return 0;
}

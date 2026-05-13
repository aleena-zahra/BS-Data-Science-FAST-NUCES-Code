//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
#include<cmath>
using namespace std;

int main(){
 
//initialise all variables
double u=1.234, p=3.334, i=0;
//take value of i from user
cout<<"Input the value of complex number i. It must be a positive number."<<endl; 
cin>>i;
//input validation
 if(i=<0)
 { 
  cout<<"The input is invalid";
 }

 else
 {

  double a = (i*i)-1;
  double b = pow(i,1.5);
  cout<<sqrt((u*b*a))/(sqrt((i*p)-2)+sqrt((i*p)-1));

 }
return 0;
}

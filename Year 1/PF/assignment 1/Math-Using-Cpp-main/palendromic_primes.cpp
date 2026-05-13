#include<iostream>
using namespace std;
   
   int main(){
   
   int flag=0,a=100,b,i=2;
   int firstDigit;
   int secondDigit;
   int thirdDigit;
   bool isPrime;
   
   cout<<"This program checks what numbers from 100 to 999 are palendromic prime numbers"<<endl;
   
   for(a=100;a<=999;a++){
   bool isPrime = true;
   for(i=2;i < a ;i++){
   
   //not prime if number completely divides
   if (a % i == 0){
   bool isPrime = false;
   break;}
   
   
  }}
  if (flag == 0){
   
   //seperate digits
   firstDigit = a % 10;
   b = a % 100;
   secondDigit = b/10; 
   thirdDigit = a/100;
   
   int newNum = firstDigit*100 + secondDigit*10 + thirdDigit;
   
   if(a == newNum)
    cout<<a<<endl;
   
   }
   
   
   
   
   return 0;
   }

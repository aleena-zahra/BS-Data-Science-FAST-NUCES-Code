#include<iostream>
using namespace std;

   int main(){
   //Armstrong numbers between 99 and 999
   
   int a=100;
   int secondDigit,firstDigit,thirdDigit,firstDigitCube , secondDigitCube , thirdDigitCube, sum;
   
   for(a = 100 ; a<=999; a++){
   
   firstDigit = a % 10;
   secondDigit = (a/10) % 10;
   thirdDigit = (a/100) % 10;
   
   firstDigitCube = firstDigit*firstDigit*firstDigit;
   secondDigitCube = secondDigit*secondDigit*secondDigit;
   thirdDigitCube = thirdDigit*thirdDigit*thirdDigit;
   
   sum = firstDigitCube + secondDigitCube + thirdDigitCube;
   
   if ( sum == a)
   cout<<a<<" is an Armstrong Number"<<endl;
   }
   return 0;
   }

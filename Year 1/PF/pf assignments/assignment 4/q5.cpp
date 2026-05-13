/*
Aleena Zahra 
23i-2514 
BDS-B 
Assignment #4
*/ 
#include <iostream>
#include<iomanip>
using namespace std;
   int main(){

 double denominator=1.0, lastTerm=0.0,number=0.0,pi, sign =1.0;
 constexpr double threshold=0.000001;

      do
      {
        number += sign * (1.0 / denominator);
        lastTerm = 1.0 / denominator;
        sign *= -1.0 ;
        denominator += 2  ;
      } while(lastTerm>threshold); 

  pi=4*number;
  cout<<"The value of pi is approximately "<<setprecision(16)<<pi<<" round off to 15 decimal places";
  
    return 0;
   }
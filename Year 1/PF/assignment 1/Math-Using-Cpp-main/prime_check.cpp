#include<iostream>
using namespace std;

   int main(){
   
   int num,flag,i=0;
   
   cout<<"This program checks if the number you enter is a prime number or not"<<endl;
   cout<<"Enter a number"<<endl;
   cin>>num;
   
   while(i < num && flag ==0){
   
   num % i;
   if (num % i == 0){
   flag = 1;
   break;
   }
   else
   i++;
  }
   if (flag == 0)
   cout<<"This number is prime"<<endl;
   else
   cout<<"This number is not prime"<<endl;
   
   return 0;
   }

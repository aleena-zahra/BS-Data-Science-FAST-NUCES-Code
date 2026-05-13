#include<iostream>
using namespace std;
   
   int main(){
   
   int num,flag,i=0;
   
   cout<<"This number checks if the number you enter is a prime number or not"<<endl;
   do {
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
   else{
   if (num<0 )
   cout<<"This number is negative so cant check";
   else
   cout<<"This number is not prime"<<endl;
   }
   }while(num>=0);
   
   
   return 0;
   }

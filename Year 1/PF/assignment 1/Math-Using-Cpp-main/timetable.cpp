#include<iostream>
using namespace std;

   int main(){
   int number,n,p=0;
   
   cout<<"Enter a number whose times table you want"<<endl;
   cin>>number;
   cout<<"Till what number do you want the table?"<<endl;
   cin>>n;
   
   for(p=1;p<=n;p++){
   
   cout<<number<<" x "<<p<<" = "<<number*p<<endl;
   }
   return 0;
   }

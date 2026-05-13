 //Prime Numbers Spiral
#include<iostream>
using namespace std;
  int main(){
  
  int num;
  int rows = 1 , columns = 1 , y = 1 , x = 0 , count = 0;
   cout << "This program checks if the numbers up til the number you enter squared are prime numbers or not"<<endl;
   cout << "Enter a number: \t";
   cin >> num;
   
   for ( columns = 1 ; columns <= num ; columns++ ){
   
     for( rows = 1; rows <= num; rows++ ){
       y = 0;
       count = 0;
       x++;
       for( y = 1; y <= x; y++){
       if((x%y) == 0)
       count ++;
       }
       
     if ( count >2 ){ //as it does divide completely on a number other than 1 and itself it isnt prime  
        cout << "| . |";
        }

       if ( count <= 2){

        cout<<"| P |";
        }  
     }
     
     cout << endl;

  }
  
  
  return 0;
  }

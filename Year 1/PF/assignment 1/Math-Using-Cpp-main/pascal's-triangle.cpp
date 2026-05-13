 //Pascals triangle
 
#include<iostream>
#include<cmath>
using namespace std;

 int main(){

  int numberOfRows;
  int i , s , a , j , num = 1 , sum = 0;
  int product=1;
    
   cout << "This program displays Pascals' Triangle for n number of rows \n";
   cout << "Enter the Number of Rows you want: ";
   cin >> numberOfRows;
  
  
  for( i = 1 ; i <= numberOfRows ; i++ ){
  
  //for space
  for( s = numberOfRows - 1 ; s >= i ; s--){
  cout << " ";
  }
  cout << 1;
  //for the rest of the numbers
  for ( j = 1 ; j < i ; j++ ){
  cout << " " ;
  num = num * ( i - j ) / (j);
  cout << num << " ";
  
  sum += num;
  product *=num;
  }
 
  
  cout << endl;
  }
  cout<<endl; 
  //sum. each row sums to 2^(row num -1)
  
  
  cout<<"The sum of "<<numberOfRows<<" number of Rows is "<<sum + numberOfRows<<endl;  
  // adding number of rows to sum to account for the ones at the front of each row 
  
  cout<<"The product of "<<numberOfRows<<" number of Rows is "<<product<<endl; 
/*
            
 
   

*/
return 0;
}

 // josephus problem 
#include <iostream>
using namespace std;

 int main(){


  int totalPeople=0, peopleSkipped=0, luckyPersonNumber=0,a=1;
  
  cout << "The Joesphus problem involves everyone standing in a circle. Counting proceeds around the circle. After a specified number of people are skipped, the next person commits suicide or is killed   with a sword. This is repeated  until only one person remains, and who is free to leave.\n\n ";
  cout << "How many people are there in the circle?\n";
  cin >> totalPeople;
  cout << "How many people do I skip each time?\n";
  cin >> peopleSkipped;
  
  while(a<=totalPeople){
    luckyPersonNumber = (luckyPersonNumber + peopleSkipped) % a;
    a++;
    }
  
  luckyPersonNumber++;	
  cout << "The lucky person who is left at the end is "<< luckyPersonNumber <<endl;
	
 return 0;
 }

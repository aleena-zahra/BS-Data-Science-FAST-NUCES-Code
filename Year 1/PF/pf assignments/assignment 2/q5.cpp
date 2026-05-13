//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
using namespace std;

int main(){
 
/*the user  will input the amount to be withdrawn. First we must check that the amount entered is from a range of 500 to 50,000. 
Then we check that it is a multiple of500. If these arent true the program cant run further. 
*/
int withdrawAmount=0;
int fiveHundredNotes=0;
int fiveThousandNotes=0;
int oneThousandNotes=0;
int leftAmount = 0;
cout<<"How much money would you like to take out?"<<endl;
cin>>withdrawAmount;

if(withdrawAmount>=500 && withdrawAmount<=50000 && withdrawAmount % 500 == 0)
{
   
// one 500 must be given minimum. If the amount has 500 at the end (example 2500, 31500) we will give one 500 note. If this isnt the case we will give two 500 notes
     if(withdrawAmount % 1000 == 500 ) 
     fiveHundredNotes = 1;
     else
     fiveHundredNotes = 2;
     
     //the amount - the five hundred bills if divided gives the number of 5k notes, and the leftover (remainder) are the 1k notes
     // example random number 47k, 47k/5k = 9k and the remainder is 2k 
     leftAmount = withdrawAmount-(fiveHundredNotes*500);
     fiveThousandNotes = leftAmount/5000;
     leftAmount = leftAmount % 5000;
     oneThousandNotes = leftAmount/1000;  
     
     
     cout<<"The withdrawl amount is "<<fiveThousandNotes<<" five thousand note(s), "<<oneThousandNotes<<" Thousand note(s) and "<<fiveHundredNotes<<" five hundred note(s)."<<endl;
 

}
else 
cout<<"Please enter an amount no less than 500 and no greater than 50,000 that is a multiple of 500."<<endl;

return 0;
}

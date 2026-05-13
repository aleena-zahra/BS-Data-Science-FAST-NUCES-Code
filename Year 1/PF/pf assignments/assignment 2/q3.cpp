//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
using namespace std;

int main(){
 
//initialise all variables
short num, shiftNum, newNum = 0;

/* multipying a number by 63 is the same as multiplying it by 64 and then subtracting that number once.   
2^(6) = 64
When we left shift a number it is multiplied with 2^(n), where n is the number of times we have right shifted the number.
So to obtain our number we will left shift the number 6 times and then subtract it once.
*/
cout<<"Enter a number:"<<endl;
cin>>num;

shiftNum = num<<6;
newNum = shiftNum - num;
cout<<"This number multiplied by 63 is "<<newNum; 

return 0;
}

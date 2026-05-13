//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
using namespace std;

int main(){
 
//initialise all variables as short since that is 2 bytes
short int totalTime, hours, minutes, seconds,leftShiftMinutes,leftShiftSeconds = 0;

cout<<"Enter a 2 byte time value."<<endl; 
cin>>totalTime;

//When we apply right shift operator and shift 12 places to the right that will get rid of the minutes and the seconds.
hours = totalTime>>12;

//When we apply left shift operator and shift 10 places to the left that will get rid of the hours and minutes.
//Then we will apply right shift operator and shift 10 places to the right to obtain the correct binary.

leftShiftSeconds = totalTime<<10;
seconds = leftShiftSeconds>>10;

/*To get rid of the seconds and hours and hence obtain the minutes, we need to use both right and left shift operators.
 We will first shift 4 spaces to the left which gets rid of the hours.
Then we will shift 10 places to the right to get rid of the seconds and hence obtain the minutes.
*/

leftShiftMinutes = totalTime<<4;
minutes = leftShiftMinutes>>10;

//in the end we will display the time
cout<<"Time is "<<hours<<" hours "<<minutes<<" minutes "<<seconds<< "seconds";
return 0;
}

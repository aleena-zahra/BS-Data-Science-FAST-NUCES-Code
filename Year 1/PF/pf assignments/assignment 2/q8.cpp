//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
using namespace std;

int main(){
 
//initialise all variables
int day, month, year,year2digits = 0;
string result;
cout<<"Enter a date in month, day, year format";
cin>>month>>day>>year;
if (month>12 || day>31)
cout<<"The input is not a valid number of days or months";

else{
// we will use mod 100 so that only the last two digits of the year are the output
year2digits = year % 100;
result= (month*day == year2digits) ? "This date is magic" : "This date is not magic";  
cout<<result;
}
return 0;
}

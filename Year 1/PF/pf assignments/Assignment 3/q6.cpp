//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
using namespace std;

int main(){
 
//initialise all variables
int workDays, salary,tax,totalPayment = 0;

cout<<"How many days of the month did you work?";
cin>>workDays;
if(workDays>30)
cout<<"Workdays cant be more than 30 days. As that is the maximum amount of days in a month"<<endl;
else{
if( workDays >= 25 && workDays<=30)
{
salary =8*workDays*900;
tax = salary*0.05;
totalPayment= salary - tax;
cout<<"You are a full-time employee. Your expected salary is "<<totalPayment;
}
else{
    if ( workDays<= 24 && workDays >=15)
    {
    salary =8*workDays*850;
    tax = salary*0.07;
    totalPayment= salary - tax;
    cout<<"You are a part-time employee. Your expected salary is "<<totalPayment;
    }
    else{
    salary =8*workDays*600;
    tax = salary*0.1;
    totalPayment= salary - tax;
    cout<<"You are an adhoc employee. Your expected salary is "<<totalPayment;
        }
    }
    
}

return 0;
}

#include<iostream>
using namespace std;

int main (){


int studentScore;
char grade;
cout<<"What is your score?";
cin>>studentScore;

(studentScore>=90)?cout<<"Your grade is A+":(studentScore>=80)?cout<<"Your grade is A":(studentScore>=70)?cout<<"Your grade is B":(studentScore>=60)?cout<<"Your grade is C":(studentScore>=50)?cout<<"Your grade is D":(studentScore<50)?cout<<"Your grade is F":cout<<"Invalid";


return 0;
}


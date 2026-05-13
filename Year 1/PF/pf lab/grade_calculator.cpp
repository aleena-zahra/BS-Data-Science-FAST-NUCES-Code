#include<iostream>
using namespace std;

int main(){
int studentScore;
cout<<"What is your score?";
cin>>studentScore;

if(studentScore>=90)
cout<<"Your grade is A+";
else if(studentScore>=80)
cout<<"Your grade is A";
else if(studentScore>=70)
cout<<"Your grade is B";
else if(studentScore>=60)
cout<<"Your grade is C";
else if(studentScore>=50)
cout<<"Your grade is D";
else if(studentScore<50)
cout<<"Your grade is F";

return 0;
}

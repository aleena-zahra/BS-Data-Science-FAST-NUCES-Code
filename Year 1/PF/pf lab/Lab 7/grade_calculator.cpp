#include<iostream>
using namespace std;

int main (){

int gpa =0;


cout<<"What is your GPA?";
cin>>gpa;

switch(gpa){
case 1:
cout<<"Your grade is c";
break;

case 2:
cout<<"Your grade is B";
break;

case 3:
cout<<"Your grade is A";
break;

case 4:
cout<<"Your grade is A+";
break;
default:
cout<<"This isnt a valid GPA";
}

return 0;
}


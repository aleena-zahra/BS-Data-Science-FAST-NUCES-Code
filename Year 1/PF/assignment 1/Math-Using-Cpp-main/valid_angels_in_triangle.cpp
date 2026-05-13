#include<iostream>
using namespace std;

int main(){

int angle1, angle2, angle3,sum;
cout<<"What is the first angle?";
cin>>angle1;
 if(angle1<0)
 cout<<"invalid option";
 else {cout<<"What is the second angle?";
 cin>>angle2;
    if(angle2<0)
    cout<<"invalid option";
        else {cout<<"What is the third angle?";
        cin>>angle3;
         if(angle1<0)
         cout<<"invalid option";

sum= angle1+angle2+angle3;
if(sum == 180)
cout<<"The triangle is valid";
else{cout<<"The triangle is not valid";}}}

return 0;
}

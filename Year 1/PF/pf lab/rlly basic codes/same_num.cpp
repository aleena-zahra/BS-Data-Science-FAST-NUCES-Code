#include<iostream>
using namespace std;

int main(){

int number;
cout<<"Enter a number:"<<endl;
cin>>number;
int variable= 2*number;
variable= 10 + variable;
variable = variable / 2;
variable = variable - number; 

cout<<"No matter what you say the answer will always be "<<variable;
return 0;
}

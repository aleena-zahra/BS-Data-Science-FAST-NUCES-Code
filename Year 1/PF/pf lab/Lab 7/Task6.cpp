#include<iostream>
using namespace std;

int main (){

double units, bill = 0;
cout<<"Enter the no of units consumed"<<endl;
cin>>units;

bill = (units <= 50)? 0.5* units: (units <=150)? 0.75* units : (units <=250)? 1.2 * units : (0.2+(units * 1.5));
cout<<"The bill is "<<bill;


return 0;
}


#include<iostream>
using namespace std;
    int main(){
    
    int number=0, newNumber=0, i=0, digit=0;

    cout << "Enter a number you want reversed: \t";
    cin >> number;

    
    for (i=number;i!=0;i /= 10){
        digit = i % 10;
        newNumber = newNumber*10 + digit;

        }

    cout << "The number "<< number <<" reversed is " << newNumber;

    
    
    
    
    return 0;
    }

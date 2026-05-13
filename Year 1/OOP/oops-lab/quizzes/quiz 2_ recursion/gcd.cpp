#include<iostream>
using namespace std;

int gcd(int num1, int num2){
    if(num2==0){
        return num1;
    }
    else{
        return gcd(num2, num1 % num2);
    }
}

int main() {
    int num1, num2;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;

    // Calculate and display the GCD
    cout << "GCD of " << num1 << " and " << num2 << " is: " << gcd(num1, num2) << endl;

    return 0;
}
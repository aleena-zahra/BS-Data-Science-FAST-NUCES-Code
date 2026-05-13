#include<iostream>
using namespace std;
int Power(int number, int power){
    if(power<0){
        return -1;
    }
    else if(power==0 && number==0){
        return -1;
    }
    else if(power==0){
        return 1;
    }
    else if(power==1){
        return number;
    }
    else {
        
        return number * Power(number,power-1);
    }
}
// int main() {
//     // Example usage:
//     int base = 0;
//     int exponent = 1;
//     cout << "Power(" << base << ", " << exponent << ") = " << Power(base, exponent) << endl;
//     return 0;
// }
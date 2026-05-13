#include <iostream>
using namespace std;

int main() {
    int n =0;
    double factorial = 1.0;
     
    cout<<"This program displays the factorial of any number you want"<<endl;
    cout << "Enter a number greater than or equal to 0: "<<endl;
    cin >> n;

    if (n < 0)
        cout << "Negative numbers arent allowed";
    else {
        for(int i = 1; i <= n; ++i) {
            factorial *= i;
           
        }
        cout << "Factorial of " << n << " is " << factorial;    
    }

    return 0;
}

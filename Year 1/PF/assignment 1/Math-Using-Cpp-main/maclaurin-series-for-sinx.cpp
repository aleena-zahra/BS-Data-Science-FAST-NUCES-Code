 // sinx calculated through maclaurin series
#include<iostream>
using namespace std; 

int main() {
 int terms, power=1, factorial=1;
 int j,i,k;
 double x, answer = 0;
 
  cout << "This program finds the maclaurin series answer for sin x"<<endl;
  cout << "What is the value of x?"<<endl;
  cin >> x;
 
  cout << "What are the number of terms?"<<endl;
  cin >> numberOfTerms;
  while (numberOfTerms <= 0) {
   cout << "Number of terms must be greater than 0 \n";
   cout << "Enter positive number of terms for Maclaurin Series: "; 
   cin >> terms;
}


cout << "Enter (positive) value of x: "; 
cin >> x;

	

 for ( i = 1; i <= terms; i++) {
      j = 2 * i - 1; 
      power = 1; 
      factorial = 1;
      
     for ( k = 1; k <= j; k++) {
      power *= x; 
      factorial *= k;
}

 if (i % 2)
 //if number is even sign is -, else its + 
 answer += static_cast<double>(power) / factorial;
 else 
 answer -= static_cast<double>(power) / factorial;
}
cout << "sin(" << x << ") = " << answer << " (correct to " << terms << " number of terms in Maclaurin series)\n";

return 0;
}

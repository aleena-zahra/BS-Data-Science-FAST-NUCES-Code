#include<iostream>
using namespace std;
void tableOfSquares (int n, int num) {
    if(num==n){
        cout << num << " " << (num * num) << endl;
        return;
    }
    else {
        cout << num << " " << (num * num) << endl;
        tableOfSquares (n, num+1);
}
}
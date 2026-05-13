#include<iostream>
using namespace std;

int sumFunction(int *n1, int *n2, int *n3, int *n4, int *n5) {
    int sum;
    sum = *n1 + *n2 + *n3 + *n4 + *n5;
    return sum;
}

int main() {
    int n[5];

    for (int i = 0; i < 5; i++) {
        cout << "Enter number " << i + 1 <<endl;
        cin >> n[i];
    }

    int TotalSum;
    TotalSum = sumFunction(&n[0], &n[1], &n[2], &n[3], &n[4]);

    cout<<"The sum of these five numbers is "<<TotalSum;

    return 0;
}

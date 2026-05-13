#include<iostream>
using namespace std;

int LargestNumber( int *a, int size){
    int biggestNum = *a;

    for (int i = 1; i < size; i++) {
        if (*(a + i) > biggestNum) {
            biggestNum = *(a + i);
        }
    }

    return biggestNum;
}

int main() {
    int size = 7;
    int a[size];

    cout << "Enter 7 numbers:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Enter number " << i + 1 << ": ";
        cin >> a[i];
    }

    int largestNumber = LargestNumber(a, size);

    cout << "The largest number from all 7 is " << largestNumber;

    return 0;
}





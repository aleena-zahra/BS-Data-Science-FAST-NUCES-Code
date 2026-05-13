#include<iostream>
#include<string>
using namespace std;

void doSomething(int **p, int size){
*p = new int[size];
for (int i = 0; i < size; i++)
(*p)[i] = i + size;
for (int i = 0; i < size; i++)
cout<< (*p)[i] << " ";
cout << endl;
}
int main(){
int rows = 3;
int ** a = new int *[rows];
for (int i = 0; i < rows; i++)
doSomething(&a[i], rows+i);
for (int i = 0; i < rows; i++)
delete[] a[i];
delete[] a;
return 0;
}
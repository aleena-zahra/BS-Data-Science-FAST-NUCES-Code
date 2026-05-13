#include<iostream>
using namespace std;

int main (){
char oper;
int n1,n2,calculatedNum;


cout<<"Menu"<<endl;
cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl;
cout<<"+ Addition"<<endl;
cout<<"- Subtraction"<<endl;
cout<<"* Multiplication"<<endl;
cout<<"/ Division"<<endl;
cout<<". Cancel"<<endl;
cout<<"Pick the operator you want"<<endl;
cin>>oper;

cout<<"Enter the first number"<<endl;
cin>>n1;
cout<<"Enter the second number"<<endl;
cin>>n2;

switch(oper){

case '+':
calculatedNum = n1 + n2;
cout<<n1<<oper<<n2<<" = "<<calculatedNum;
break;

case '-':
calculatedNum = n1 - n2;
cout<<n1<<oper<<n2<<" = "<<calculatedNum;
break;

case '*':
calculatedNum = n1 * n2;
cout<<n1<<oper<<n2<<" = "<<calculatedNum;
break;

case '/':
calculatedNum = n1 / n2;
cout<<n1<<oper<<n2<<" = "<<calculatedNum;
break;

case '.':
default :
cout<<"Cancelling Program";

}





return 0;
}


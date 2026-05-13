#include<iostream>
using namespace std;

   void StringConcatination(char a[] , char b[]);
   int getLenght(char a[]);
  
   int main(){
   //declare strings
    char stringOne[100]={};
    char stringTwo[100]={};
   //get values from user 
   cout<<"Enter string 1\n";
   cin.getline(stringOne,100);
   cout<<"Enter string 2\n";
   cin.getline(stringTwo,100);
   
   cout<<"After getting input string one is: "<<stringOne<<endl;
   cout<<"After getting input string two is: "<<stringTwo<<endl;
   cout<<"Both Strings concatinated together are "<<endl;
   StringConcatination(stringOne, stringTwo);
   
   }
   void StringConcatination(char a[], char b[]){
     const int maxSize = 100; // Adjust the size as needed
    char concatinatedString[maxSize];
     int i=0;
     for( i=0; a[i] !='\0'; i++){
     concatinatedString[i]=a[i];
     }
     for(int j=0; b[j]!='\0'; j++){
     concatinatedString[i]=b[j];
     i++;
     }
     concatinatedString[i] = '\0';
     
       cout<<concatinatedString;
      
   }

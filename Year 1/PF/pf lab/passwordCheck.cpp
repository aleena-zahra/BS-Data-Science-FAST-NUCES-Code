#include<iostream>
using namespace std;

   void StringConcatination(char a[] , char b[]);
   int getLenght(char a[]);
   bool isValid(char password[]);
   int main(){
   
   char password[15];
   cout<<"\nEnter a password\n";
   cin.getline(password,15);
   cout<<"Your password is: "<<password<<endl;
   bool validLenght=false;
   int lenght = getLenght(password);
   if (lenght>=8) validLenght=true;
   if(!validLenght){
   cout<<"Your password has "<<lenght<<" digits. Passwords must be 8 or more digits.\n";
   }
   else{
       bool valid = isValid(password);
       if (valid) cout<<"Password is valid\n";
       else  cout<<"Password is not valid\n";
   }
   return 0;
   }
   
   int getLenght(char a[]){
   int lenght=0;
   for(int i=0; a[i]!='\0';i++){
   lenght++;
   }
   return lenght;
   }
   bool isValid(char password[]){
   bool specialChar=false;
   bool number=false;
   bool capLetter=false;
   bool smallLetter=false;
   for(int i=0;i<15;i++){
   if(password[i] >= 'A' && password[i] <= 'Z') capLetter=true;
   if(password[i] >= 'a' && password[i] <= 'z') smallLetter=true;
   if(password[i] >= '0' && password[i] <= '9') number=true;
   if(password[i] == '@' || password[i] == '#' || password[i] == '$' || password[i] == '%' || password[i] == '(' || password[i] == ')'
   || password[i] == '+' || password[i] == '='  || password[i] == '-' || password[i] == '!' || password[i] == '&' || password[i] == '*') specialChar=true;
   
   
   }
   if(!capLetter)     cout<<"Password must contain atleast one Capital Letter\n";
   if(!smallLetter)  cout<<"Password must contain atleast one Small Letter\n";
   if(!number)       cout<<"Password must contain atleast one Number\n";
   if(!specialChar) cout<<"Password must contain atleast one Special Character\n";
   
   if( specialChar==true &&  number==true && capLetter==true &&  smallLetter==true) return 1;
   else return 0;
   }

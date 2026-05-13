 // Aleena Zahra BDS-1B 23i-2514
 #include<iostream>
 #include<string>
 using namespace std;
  int main(){
  int userNum=0, division=1,remainder=0,i=1;
  int base =0, newNum=0;
  string rev;
   string stringremainder = " ";
  /*
  To convert decimal number to another base these are the steps we take: 
  Divide decimal number by new base
  Remainder is the least significant and first digit
  Divide the quotient of the previous divide by the new base.
  The remainder is the next digit of new number. AND SO ON....
  
    divide the number by base
    write down the remainder
    repeat the process with the integer part of the division
    stop when you reach zero
    the remainders in reverse order give you the digits in base

  */
  
   cout<<"Enter a decimal number: ";
   cin>>userNum;
  
   cout<<"Enter base to convert to: ";
   cin>>base;
   
   while( base<2 || base>16){
    cout<<"INVALID BASE! \n";
    cout<<"Please enter base from 2 to 16";
    cin>>base;
   }
   
   
     division = userNum;
    
     while(division !=0){
     //the biggest value of division can be the base number -1. Like take number 89, the division with 9 would be 8, and thats the most it can be divided
      
   
      
      if(base<=10){
       division /= base;
      remainder = division % base;
      newNum += remainder*i;
      i *= 10;
      }
      
      else{
      
      
      
      
      remainder = division % base;
      division /= base;
      
      
      
      
      if (remainder == 10)
      stringremainder ="A";
      else if (remainder == 11)
      stringremainder ="B";
      else if (remainder == 13)
      stringremainder ="D";
      else if (remainder == 12)
      stringremainder ="C";
      else if (remainder == 14)
      stringremainder ="E";
      else if (remainder == 15)
      stringremainder ="F";
     
   
    
      stringremainder = to_string(remainder) + stringremainder;
      cout << "String remainder: " << stringremainder << endl;
     }
     
     
     

     }
     if(base<10)
     cout << " The number converted from decimal to base " << base << " is " << newNum ;
     else
     cout << " The number converted from decimal to base " << base << " is " << stringremainder ;
    
 
  return 0;
  }

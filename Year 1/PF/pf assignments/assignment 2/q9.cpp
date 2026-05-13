//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<ctime>
using namespace std;

int main(){
  //seed for generating random nums
  srand(time(0));


  char negativeNumsAllowed;
  char oper;
  int maximumValue,n1,n2,solution,userSolution = 0;
 
  cout<<"Enter the operand for whose operation you want to generate an exercise"<<endl;
  cin>>oper;
  cout<<"What is maximum number that should be allowed in the exercise?"<<endl;
  cin>>maximumValue;
  cout<<"Are negative values allowed in the exericise? Enter Y for Yes or N for No"<<endl;
  cin>>negativeNumsAllowed;

  /*
  Now to calculate range, if negative numbers are allowed we will have a different range as     opposed to when they arent allowed. So we use if-else statement
  */
 
   if (negativeNumsAllowed == 'N'){
    // when we take modulus with a number + 1 the range will be from 0 to that number. So taking  the example of 20: (rand() % (20 + 1 ) ) means any random number produced will be from 0 to 20.
    n1 = (rand() % (maximumValue + 1));
    n2 = (rand() % (maximumValue + 1));
    }

  else {
   
    /*lets say the maximum value entered by user is 20. so we need or random numbers to be  between 
 -20 and 20 for this we take a range of 40. half numbers will be negative and half will be 0 and positive numbers. This way our range will be from -20 to 20 and any generated number whos mod gives less than half value will become negative
    */ 
    n1 = rand() % (2* maximumValue + 1) - maximumValue;
    n2 = rand() % (2* maximumValue + 1) - maximumValue;
    }   

    
   switch(oper){

   case '+':
   cout<<"The Addition Exercise is "<<n1<<" + "<<n2;
   solution = n1 + n2;
   break;


   case '-':
   if (negativeNumsAllowed == 'N'){
     if(n1>=n2){
      cout<<"The Subtraction Exercise is "<<n1<<" - "<<n2;
      solution = n1 - n2;
      }
     else {   //here n2 is less than n1
       /*To prevent the second number from being less than the first number. We first check if  this is 
      the case. If it is so we will swap their positions so that the subtraction doesnt result in a  
       negative  number*/
  
      cout<<"The Subtraction Exercise is "<<n2<<" - "<<n1;
      solution = n2 - n1;
       }
       
    }
    else{
     cout<<"The Subtraction Exercise is "<<n1<<" - "<<n2;
     solution = n1 - n2;}
   break;


   case '*':
   cout<<"The Multiplication Exercise is "<<n1<<" x "<<n2;
   solution = n1 * n2;
   break;


  case '/':
   if (n2 != 0 ){
    cout<<"The Division Exercise is "<<n1<<" / "<<n2;
    solution = n1/n2;}
   else{
    cout<<"The Division Exercise is "<<n2<<" / "<<n1;
    solution = n2/n1;
    }
  break;

 
  default:
    cout<<"The operant you entered is invalid"<<endl;
  return 1;
   
   }

  cout<<"Enter the solution"<<endl;
  cin>>userSolution;
   if (userSolution == solution)
     cout<<"Congratulations!!! Your solution is correct!! Good job, you've made your parents proud";
   else
   cout<<"Oh no, looks like your solution is wrong. Better luck next time!"<<endl;

return 0;
}

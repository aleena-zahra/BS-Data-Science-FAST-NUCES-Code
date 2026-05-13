//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;


int main(){
//seed for generating random nums
  srand(time(0));
//declare all variables
int firstNumber,secondNumber =0;
char guess;
int num = 0;


cout<<"Higher or Lower Game"<<endl;
//to generate nums between 1 and 20, generate nums between 0 and 19 and then add 1

firstNumber = (rand() % 20) + 1;
secondNumber = (rand() % 20) + 1;
 
cout<<"The first number is "<<firstNumber<<endl;
cout<<"If you think the second number is higher enter H. If you think it's lower enter L."<<endl;
cin>>guess;


    switch(guess){
    case 'H':
    if (secondNumber > firstNumber)
      cout<<"You are right! You won!!"<<endl;
     else
      cout<<"Oh no, you guessed wrong. You lose"<<endl;
    break;
   
    case 'L':
     if (secondNumber<firstNumber)
      cout<<"You are right! You won!!"<<endl;
     else
      cout<<"Oh no, you guessed wrong. You lose"<<endl;
    break;
   
    default:
      cout<<"Either enter H for Higher or L for Lower. Other inputs are not acceptable";
    break;
  }
return 0;
}

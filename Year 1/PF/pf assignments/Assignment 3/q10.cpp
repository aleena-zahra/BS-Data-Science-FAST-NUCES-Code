//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;


int main(){
//declare all variables
int gameChoice;
int firstNumber,secondNumber =0;
char guess;
int num = 0;
char computerChoice;
char userChoice;
int num1,num2,num3;
int guess1, guess2, guess3 =0;


cout<<"1. Play Higher or Lower"<<endl;
cout<<"2. Play paper - scissors - rock"<<endl;
cout<<"3. Guess the numbers"<<endl;
cout<<"4. Quit"<<endl;
cout<<"Enter your choice (1 - 4)"<<endl;
cin>>gameChoice;


switch(gameChoice){


case 1:
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
break;

case 2:
// We will generate a random number from 1 to 3 where 1 = paper, 2 = scissors, 3 = rock
num = (rand() % 3) + 1;


if(num == 1)
 computerChoice = 'P';
if(num == 2)
 computerChoice = 'S';
if(num == 3)
 computerChoice = 'R';


cout<<"Rock, Paper, Scissors?"<<endl;
cout<<" To pick rock enter R"<<endl;
cout<<"To pick paper enter P"<<endl;
cout<<"To pick scissors enter S"<<endl;

cin>>userChoice;

if(userChoice != 'P' && userChoice != 'S' && userChoice != 'R'){
cout<<"Whoops, that isn't an option! Looks like you dont follow instructions very well."<<endl;}
else{


   switch (computerChoice){
   case 'P':
   if (userChoice == 'P')
   cout<<"That was a draw since I also picked Paper"<<endl;
   if (userChoice == 'S')
   cout<<"Aww, dang it! You won! I picked Paper"<<endl;
   if (userChoice == 'R')
   cout<<"You lost since I picked Paper"<<endl;
   break;

   case 'S':
   if (userChoice == 'P')
   cout<<"You lost since I picked Scissor"<<endl;
   if (userChoice == 'R')
   cout<<"Aww, dang it! You won! I picked Scissor"<<endl;
   if (userChoice == 'S')
   cout<<"That was a draw since I also picked Scissors"<<endl;
   break;
   
   case 'R':
   if (userChoice == 'S')
   cout<<"You lost since I picked Rock"<<endl;
   if (userChoice == 'P')
   cout<<"Aww, dang it! You won! I picked Rock"<<endl;
   if (userChoice == 'R')
   cout<<"That was a draw since I also picked Rock"<<endl;
   break;
   }
}
break;
   
case 3:
//Generating 3 random nums fo guessing game


 num1 = (rand() % 10);
 num2 = (rand() % 10);
 num3 = (rand() % 10);
cout<<"Pick 3 number guesses that are any 3 different numbers from 0 to 9"<<endl;
cin>>guess1>>guess2>>guess3;

//input validation
if ((guess1 > 9 || guess1 < 0) || (guess2 > 9 || guess2 < 0) || (guess3 > 9 || guess3 < 0)){
cout<<"Your guesses are out of range. "<<endl;
}
else{

   if (guess1 == num1 && guess2 == num2 && guess3 == num3)
   cout<<"Your guesses are correct and match the order of numbers perfectly!!"<<endl;
   
   else{
     if((guess1 == num1 || guess1 == num2 || guess1 == num3) && (guess2 == num1 || guess2 == num2 || guess2 == num3) && (guess3 == num1 || guess3 == num2 || guess3 == num3 )){
     cout<<"Your guesses are correct but arent in order"<<endl;
     cout<<"The numbers in correct order were "<<num1<<" "<<num2<<" "<<num3<<endl;}
     else{
       if(((guess1 == num1 || guess1 == num2 || guess1 == num3) && (guess2 == num1 || guess2 == num2 || guess2 == num3 )) || ((guess1 == num1 || guess1 == num2 || guess1 == num3) && (guess3 == num1 || guess3 == num2 || guess3 == num3)) || ((guess2 == num1 || guess2 == num2 || guess2 == num3) && (guess3 == num1 || guess3 == num2 || guess3 == num3))){
       cout<<"Two of your guesses are correct"<<endl;
       cout<<"The numbers were "<<num1<<" "<<num2<<" "<<num3<<endl;}
       else{  
         if(guess1 == num1 || guess1 == num2 || guess1 == num3 || guess2 == num1 || guess2 == num2 || guess2 == num3 || guess3 == num1 || guess3 == num2 || guess3 == num3 ){
      cout<<"One of your guesses matches one of the 3 numbers"<<endl;
      cout<<"The numbers were "<<num1<<" "<<num2<<" "<<num3<<endl;}
         else{
          cout<<"None of your guesses are correct. Better luck next time!"<<endl;
          cout<<"The numbers were "<<num1<<" "<<num2<<" "<<num3<<endl;}


}}}}
break;


case 4:
cout<<"Quitting Game Program. Goodbye."<<endl;
break;
default:
cout<<"There are only 4 options and so your choice is invalid"<<endl;
}


return 0;
}




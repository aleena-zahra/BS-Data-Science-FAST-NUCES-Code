//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;


int main(){
//seed for generating random nums
  srand(time(0));
//declare all variables
int num = 0;
char computerChoice;
char userChoice;

cout<<"Rock, Paper, Scissors?"<<endl;
// We will generate a random number from 1 to 3 where 1 = paper, 2 = scissors, 3 = rock
num = (rand() % 3) + 1;


if(num == 1)
 computerChoice = 'P';
if(num == 2)
 computerChoice = 'S';
if(num == 3)
 computerChoice = 'R';



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
return 0;
}
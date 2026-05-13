//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2


#include<iostream>
using namespace std;

int main(){
 
//initialise all variables
int totalEggs,leftoverEggs, eggBoxes = 0;
cout<<"How many eggs do you want to pack?";
cin>>totalEggs;

//eggs cant be negative numbers so if the user enters negative values or fractions this program will not run
if(totalEggs<0 )
cout<<"Sorry, The eggs you want to pack can only be positive integers.";
else{

// for all box types we will find and display the number of boxes needed and the leftover eggs
eggBoxes = totalEggs / 30;
leftoverEggs = totalEggs % 30;
cout<<"The number of egg  Boxes needed when each box has 30 eggs is: "<<eggBoxes<<endl;
cout<<"And The number of eggs that will be leftover is "<<leftoverEggs<<endl;

eggBoxes = totalEggs / 24;
leftoverEggs = totalEggs % 24;
cout<<"The number of egg Boxes needed when each box has 24 eggs is: "<<eggBoxes<<endl;
cout<<"And number of eggs that will be leftover is "<<leftoverEggs<<endl;

eggBoxes = totalEggs / 18;
leftoverEggs = totalEggs % 18;
cout<<"The number of egg Boxes needed when each box has 18 eggs is: "<<eggBoxes<<endl;
cout<<"And number of eggs that will be leftover is "<<leftoverEggs<<endl;

eggBoxes = totalEggs / 12;
leftoverEggs = totalEggs % 12;
cout<<"The number of egg Boxes needed when each box has 12 eggs is: "<<eggBoxes<<endl;
cout<<"And number of eggs that will be leftover is "<<leftoverEggs<<endl;

eggBoxes = totalEggs / 6;
leftoverEggs = totalEggs % 6;
cout<<"The number of egg Boxes needed when each box has 6 eggs is: "<<eggBoxes<<endl;
cout<<"And number of eggs that will be leftover is "<<leftoverEggs<<endl;
}
return 0;
}

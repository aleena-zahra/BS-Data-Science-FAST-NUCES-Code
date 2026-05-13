//ALEENA ZAHRA 23I-2514 ASSIGNMENT 2
#include<iostream>
using namespace std;

int main(){
//initialize variables 
int n1, n2;
bool n1b = 0, n2b = 0, n1r = 0, n2r = 0, n1g = 0, n2g = 0;	
//input both tile numbers
cout << "Enter n1: "; cin >> n1;
cout << "Enter n2: "; cin >> n2;

//if user input is outside of range terminate program after displaying error
  if (n1 < 1 || n1 > 81 || n2 < 1 || n2 > 81)
  cout << "One or both numbers not in grid."<<endl;
  
  else {
  //decrement both numbers by 1
  n1--; n2--;
  //take modulus to find if row is even or odd for first number
    if ((n1 / 9) % 2) {
       //if the row is even (example, 2nd row, 4th row etc) 
       //check color according to pattern of even rows. the pattern is blue, red, gray (left to right order)
        if (n1 % 3 == 0) 
       //if first number is a multiple of 3 its a blue tile
       n1b = 1;
       else 
       // if first number isnt a multiple of 3 and instead is a tile after that its a red tile
        if (n1 % 3 == 1) 
         n1r = 1;
        else
         //otherwise its a tile after that which is gray 
         n1g = 1;
	  }
    else {
    //if the row is odd (1st row ,3rd row etc)
    //if first number is a multiple of 3 its a gray tile. Because the order is gray, blue, red (from left to right)and we decremented our number in the start. So hence multiple of 3 is now gray.
     if (n1 % 3 == 0) 
     n1g = 1;
      else 
      //if number isnt a multiple of 3 and instead is a tile after that its a blue tile
       if (n1 % 3 == 1) 
       n1b = 1;
        else
        // otherwise its a tile after that which is red 
        n1r = 1;
         }
 
 // for second number we check if its on an even or odd row        
    if ((n2 / 9) % 2) {
    //for when row is even
     if (n2 % 3 == 0) 
     // if second number is a multiple of 3 its a blue tile
      n2b = 1;
      else  
      // if second number isnt a multiple of 3 and instead is a tile after that its a red tile
       if (n2 % 3 == 1) 
       n2r = 1;
        else 
        //otherwise its a tile after that which is gray
        n2g = 1;
	  }
    else {
    //for when row is odd
    //if second number is a multiple of 3 its a gray tile
     if (n2 % 3 == 0) 
     n2g = 1;
      else 
       // if second number isnt a multiple of 3 and instead is a tile after that its a blue tile
       if (n2 % 3 == 1) 
       n2b = 1;
        else 
        // otherwise its a tile after that which is red
        n2r = 1;
         }
        }
//if both n1b and n2b are true both tiles are blue and so on for the other colors. Otherwise the tile colors dont match
if (n1b && n2b) 
cout << "Both tiles are Blue"<<endl;
 else 
  if (n1g && n2g) 
  cout << "Both tiles are Grey"<<endl;
  else 
  if (n1r && n2r) 
  cout << "Both tiles are Red"<<endl;
   else 
   cout << "Both tiles are Different"<<endl;

return 0;
}

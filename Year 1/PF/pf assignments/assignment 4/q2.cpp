/*
Aleena Zahra 
23i-2514 
BDS-B 
Assignment #4
*/ 
#include <iostream>
#include <cstdlib> 
#include <ctime> 
using namespace std;
   int main(){
    srand(time(0));
    
    int n,rows,columns,columnNumber,rowNumber;

    cout<<"Enter the lenght of square matrix: \t";
    cin>>n;
    
    int matrix[n][n];

    for( rows=0;rows<n;rows++){
        for( columns=0;columns<n;columns++){
            //generate random number
            matrix[rows][columns] = rand() % 100;
            cout<<matrix[rows][columns]<<" ";

        }
       cout<<endl;
    }
    //printing pattern
    cout<<"The pattern according to the Matrix above is \n";

     int goUpwards = 0, goLeftwards = 0, goRightwards = n,  goDownwards = n;
     goRightwards--;  
     goDownwards--;

    while (goUpwards <= goDownwards && goLeftwards <= goRightwards){
    
    for(columns= goLeftwards;columns<=goRightwards;columns++){
            //print first row
           
            cout<<matrix[goUpwards][columns]<<" -> ";
    }
    goUpwards++;
   
    
    for(rows=goUpwards;rows<=goDownwards;rows++){
            //print first row
           
            cout<<matrix[rows][goRightwards]<<" -> ";
    }
   
    goRightwards--;
    if(goUpwards<=goDownwards){
        for (columns = goRightwards; columns >= goLeftwards; columns--)
        {
        cout<<matrix[goDownwards][columns]<<" -> ";
         }
     
      goDownwards--;
   }
   if(goLeftwards<=goRightwards){
    for(rows=goDownwards; rows>= goUpwards; rows--){
        cout<<matrix[rows][goLeftwards]<<" -> ";
    }
    goLeftwards++;
   }
   }
    return 0;
   }
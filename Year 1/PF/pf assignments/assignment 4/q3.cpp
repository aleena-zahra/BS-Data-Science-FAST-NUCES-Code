/*
Aleena Zahra 
23i-2514 
BDS-B 
Assignment #4
*/ 
#include <iostream>
using namespace std;
   int main(){
    int n,count=0;
    cout<<"What is the lenght of square matrix?";
    cin>>n;
    // The depth is fixed at 3, and each 2D layer must be a minimum of 8 x 8. Allowable matrix sizes include (3, 8, 8), (3, 10,10), (3, 16, 16), and so on.
    // the number has to be divisible by 2 so it can be seperated into quadrants appropriately. This wouldnt work for 9x9
    while (n<8 || n % 2 !=0)
    {
        cout<<"The value of n isnt valid please enter a number like 8,10,16 etc";
        cout<<"What is the lenght of square matrix?";
        cin>>n;

    }
    

    int arr[3][n][n];
    //Initialize the values of the first layer to zeros, the second layer to ones, and the third layer to twos.
    for (int i = 0; i < 3; i++)
    {
        cout<<"Layer "<<i<<endl;
        for (int rows = 0; rows < n; rows++)
        {
            for (int columns = 0; columns < n; columns++)
            {
                
                arr[i][rows][columns]= i;
                cout<<arr[i][rows][columns];
            }
            cout<<endl;
            
        }
        
    }
    //Generate N random numbers for each quadrant, where N is calculated as (elements in quadrant ((n*n)/4) divided by 8).
    int RandomNumbersForQuad1, RandomNumbersForQuad2, RandomNumbersForQuad3,RandomNumbersForQuad4;
    
    //each quad will have same number of elements so each element has N random numbers
    int N = ((n*n)/4)/8;

    //The range of the random numbers for each quadrant should fall within the respective quadrant’s indexes.
    //so random numbers for each quad are different
    //the range for quad1 and 2 are from 0 to n-1, for quad 1 its half those values so, [0] to [n-1/2], then quad 2 is [n-1/2 +1]  to  [n-1]
    //quad 3 is [same as quad 2 start][0]
    //quad 1 is [0][0] to [n-1/2][n-1/2]
    //quad 2 is [][]

    int maxRowIndexQuad1;
    int maxColumnIndexQuad1;


    




    return 0;
   }
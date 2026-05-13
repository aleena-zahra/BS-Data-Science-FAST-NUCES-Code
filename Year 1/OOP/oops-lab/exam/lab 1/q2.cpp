#include<iostream>
using namespace std;
//bool allSpacesNotFilled(int magicSquare[][3],int squareDimension);
void magicSquare(const int squareDimension){
    int num = 1;
    int magicSquare[squareDimension][squareDimension];

    //initialize magic square to all 0's
    for (int i =0 ; i< squareDimension; i++){
        for (int j =0 ; j< squareDimension; j++){
                magicSquare[i][j] = 0;
        }
    }
    int i = 0;
    bool check=0;
    int j = squareDimension / 2;
    int positionx;
    int positiony;
    while(num <= (squareDimension * squareDimension)){
        if (i == -1 && j == squareDimension) {
            j = squareDimension - 1;
            i = 0;
        }
        else {
            if (j == squareDimension) {
                j = 0;
            }
            if (i < 0) {
                i = squareDimension - 1;
            }
        }
        //if space is already filled 
        if (magicSquare[i][j] !=0) {
            if(i==squareDimension-1 && j==0){
                i=0;
                j=squareDimension-1;
                check=1;
            }
            else{
                i=positionx+1;
                j=positiony;
            }
            continue;
        } 
        else {
            magicSquare[i][j] = num;
            num++;
        } 
        if(check){
            i++;
        }
        else{
            positionx=i;
            positiony=j;
            i--;
            j++;
        }
        check=0;          
    }
    
    //lastly display the square
    for (int i = 0; i < squareDimension; i++) {
        for (int j = 0; j < squareDimension; j++) {
            cout << magicSquare[i][j] << " ";
        }
        cout << endl;
    }

}
int main(){
    magicSquare(3);
    magicSquare(5);
    magicSquare(7);
    magicSquare(9);
    return 0;   
}

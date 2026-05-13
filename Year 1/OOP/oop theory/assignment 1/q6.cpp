/*Aleena Zahra 23i-2514 BDS-2B Assignment 1 OOP*/
#include<iostream>
using namespace std;
void makePattern(char symbol,char **p,int numberOfRows,int numberOfColumns);
void printArray(char **p,int numberOfRows,int numberOfColumns);
void transposeArray(char **p, int numberOfRows, int numberOfColumns); 
void columnSwap(char **p, int numberOfRows, int numberOfColumns);
void backwardsRowsArray(char **p, int numberOfRows, int numberOfColumns);
void encryptArray(char **p,int numberOfRows,int numberOfColumns);
void decryptArray(char **p,int numberOfRows,int numberOfColumns);
void updateArray(char symbol1,char symbol2,char **p,int numberOfRows,int numberOfColumns,int rowPosition, int colPosition);
void deallocateMemory(char **p,int numberOfRows);
int main(){
    int numberOfRows=5,numberOfColumns=5;
    char arr[numberOfRows][numberOfColumns];
    char **p = new char*[numberOfRows]; // 2D pointer

    for(int i = 0; i < numberOfRows; i++) {
        p[i] = arr[i]; // Assign the address of each row to the 2D pointer
    }
    char symbol;
    cout<<"Enter the symbol to draw the Pattern with:\t";
    cin>>symbol;
    makePattern(symbol,p,numberOfRows,numberOfColumns);
    cout<<"\nThe Assignment was Easy :))) \n";
    printArray(p,numberOfRows,numberOfColumns);
    encryptArray(p,numberOfRows,numberOfColumns);
    cout<<"\nAfter Encryption:\n";
    printArray(p,numberOfRows,numberOfColumns);
    decryptArray(p,numberOfRows,numberOfColumns);
    cout<<"\nAfter Decryption:\n";
    printArray(p,numberOfRows,numberOfColumns);
    char symbol2;
    cout<<"\nEnter a symbol\t";
    cin>>symbol2;
    int rowPosition,colPosition;
    do{
    cout<<"\nEnter a row Position\t";
    cin>>rowPosition;
    }while(rowPosition<0 || rowPosition>4);
    do{
    cout<<"\nEnter a column Position\t";
    cin>>colPosition;
    }while(colPosition<0 || colPosition>4);
    updateArray(symbol,symbol2,p,numberOfRows,numberOfColumns,rowPosition,colPosition);
    printArray(p,numberOfRows,numberOfColumns);
    deallocateMemory(p,numberOfRows);
    return 0;

}

void makePattern(char symbol,char **p,int numberOfRows, int numberOfColumns){
    for(int i=0; i<numberOfRows; i++){
        for(int j=0; j<numberOfColumns; j++){
            if(i==0 || j==0 ||i==2||i==4){
                p[i][j]=symbol;
            }
            else{
                p[i][j]=' ';
            }
        }
    }
}
void printArray(char **p,int numberOfRows,int numberOfColumns){
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            // Access elements using 2D pointer
            cout << p[i][j] << "  "; 
        }
        cout << endl;
    }
    cout<<endl<<endl;
}
void encryptArray(char **p,int numberOfRows,int numberOfColumns){
    //rotate 90 anticlock direction
    columnSwap(p,numberOfRows,numberOfColumns);
    transposeArray(p,numberOfRows,numberOfColumns);
    backwardsRowsArray(p,numberOfRows,numberOfColumns);
}
void decryptArray(char **p,int numberOfRows,int numberOfColumns){
    //rotate again by 90+90+90 degrees
    columnSwap(p,numberOfRows,numberOfColumns);
    transposeArray(p,numberOfRows,numberOfColumns);
    backwardsRowsArray(p,numberOfRows,numberOfColumns);
    columnSwap(p,numberOfRows,numberOfColumns);
    transposeArray(p,numberOfRows,numberOfColumns);
    backwardsRowsArray(p,numberOfRows,numberOfColumns);
    columnSwap(p,numberOfRows,numberOfColumns);
    transposeArray(p,numberOfRows,numberOfColumns);
    backwardsRowsArray(p,numberOfRows,numberOfColumns);
}
void transposeArray(char **p, int numberOfRows, int numberOfColumns) {
    char temp='=';
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = i; j < numberOfColumns; j++) {
            char temp = p[j][i];
            p[j][i] = p[i][j];
            p[i][j] = temp;
        }
    }
}
void backwardsRowsArray(char **p, int numberOfRows, int numberOfColumns) {
    int lastRowPosition= numberOfRows-1;
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns/2; j++) {
            char temp = p[i][j];
            p[i][j] = p[i][lastRowPosition-j];
            p[i][lastRowPosition-j] = temp;
        }
        
    }
}
void columnSwap(char **p, int numberOfRows, int numberOfColumns) {
    for (int i = 0; i < numberOfColumns / 2; i++) {
        for (int j = 0; j < numberOfRows; j++) {
            char temp = p[j][i];
            p[j][i] = p[j][numberOfColumns - 1 - i];
            p[j][numberOfColumns - 1 - i] = temp;
        }
    }
}

void updateArray(char symbol1,char symbol2,char **p,int numberOfRows,int numberOfColumns,int rowPosition, int colPosition){
    for(int i=0; i<numberOfRows; i++){
        for(int j=0; j<numberOfColumns; j++){
            if(i==rowPosition && j== colPosition){
                if(p[i][j]==symbol1)
                p[i][j]=symbol2;
                else{
                    cout<<"\nUpdate Not Possible as coordinates outside of Shape";
                }
            }
        }
    }
    
}
void deallocateMemory(char **p, int numberOfRows){
     // Deallocate memory for 2D array
    for (int i = 0; i < numberOfRows; i++) {
        delete[] p[i];
    }
    delete[] p;
    }
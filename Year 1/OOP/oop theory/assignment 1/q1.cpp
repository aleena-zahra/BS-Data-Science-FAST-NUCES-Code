/*Aleena Zahra 23i-2514 BDS-2B Assignment 1 OOP*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void allocateMemory(char **&arr,int numberOfRows,int numberOfColumns);
void deallocateMemory(char **arr,int numberOfRows);
void printArray(char **arr,int numberOfRows,int numberOfColumns);
void findWord(string userWord,char **arr,int numberOfRows,int numberOfColumns);
void checkHorizontallyForwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord, int wordIndex,int lengthOfUserWord);
void checkHorizontallyBackwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord, int wordIndex,int lengthOfUserWord);
void checkVerticallyBackwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord, int wordIndex,int lengthOfUserWord);
void checkVerticallyForwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord, int wordIndex,int lengthOfUserWord);
void checkDiagonallyBackwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord, int wordIndex,int lengthOfUserWord);
void checkDiagonallyForwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord, int wordIndex,int lengthOfUserWord);
int stringLength(string str);
int main(){
    int numberOfColumns=9,numberOfRows=10;
    char **puzzleArr,c;
    allocateMemory(puzzleArr,numberOfRows,numberOfColumns);
    ifstream infile("boggle.txt");
    int i=0,j=0;
    while (infile.get(c)) {
        if (c == '\n') {
            i++;
            j=0;
        } else {
            puzzleArr[i][j]=c;
            j++;
        }
    }
    printArray(puzzleArr,numberOfRows,numberOfColumns);
    string userWordStr;

    // bool wantToExit = false;
    // while(!wantToExit){
    cout<<"\nFind a word from the crossword\n";
    cin>>userWordStr;
    int wordLength=stringLength(userWordStr);
    //make char array to store userWord string
    char *userWord;
    //allocate memory thats word length + \0
    userWord = new char[wordLength+1];
    //copy elements of string to char array
    for (int i=0; i<=wordLength ; i++){
        userWord[i]=userWordStr[i];
    }
    //traverse 2D array to look for the first letter
    for(int i=0; i<numberOfRows; i++){
        for(int j = 0; j < numberOfColumns; j++){
            if(puzzleArr[i][j]==userWord[0]){
                checkHorizontallyForwards(i,j+1,numberOfRows,numberOfColumns,puzzleArr,userWord,1,wordLength);
                checkHorizontallyBackwards(i,j-1,numberOfRows,numberOfColumns,puzzleArr,userWord,1,wordLength);
                checkVerticallyBackwards(i-1,j,numberOfRows,numberOfColumns,puzzleArr,userWord,1,wordLength);
                checkVerticallyForwards(i+1,j,numberOfRows,numberOfColumns,puzzleArr,userWord,1,wordLength);
                checkDiagonallyBackwards(i-1,j-1,numberOfRows,numberOfColumns,puzzleArr,userWord,1,wordLength);
                checkDiagonallyForwards(i+1,j+1,numberOfRows,numberOfColumns,puzzleArr,userWord,1,wordLength);
            }
        }
    }
    // cout<<"\nPress 1 to Exit, 0 to Continue:\t";
    // cin>>wantToExit;
    // }
    delete[] userWord;
    deallocateMemory(puzzleArr,numberOfRows);
    return 0;

}

void allocateMemory(char **&arr,int numberOfRows,int numberOfColumns){
    arr = new char*[numberOfRows];
    for (int i = 0; i < numberOfRows; i++) {
        arr[i] = new char[numberOfColumns];
    }    
    meow meow meow
}
void deallocateMemory(char **arr, int numberOfRows){
    for (int i = 0; i < numberOfRows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    }
void printArray(char **arr,int numberOfRows,int numberOfColumns){
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            cout << arr[i][j] << "  "; 
        }
        cout << endl;
    }
    cout<<endl<<endl;
}
int stringLength(string str){
    int length=0;
    for(int i=0 ; str[i]!='\0';i++){
        length++;
    }
    return length++;
}
void checkHorizontallyForwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord , int wordIndex, int lengthOfUserWord){
    
    if (rowIndex>0 && columnIndex>0 && rowIndex<numberOfRows && columnIndex<numberOfColumns){
        if(userWord[wordIndex]==puzzleArr[rowIndex][columnIndex]){
            if ( wordIndex == lengthOfUserWord-1){
                cout << "Word found Horizontally forwards!!" << endl;
                cout << "Word from ( "<<rowIndex<<","<<columnIndex-lengthOfUserWord+1<<" ) "<<" to ( "<<rowIndex<<","<<columnIndex<<" ) " << endl;
                return;
            }
            else {
                checkHorizontallyForwards(rowIndex,columnIndex+1,numberOfRows,numberOfColumns,puzzleArr,userWord,wordIndex+1,lengthOfUserWord);
            }
        }
    }
}
void checkHorizontallyBackwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord , int wordIndex, int lengthOfUserWord){
    
    if (rowIndex>0 && columnIndex>0 && rowIndex<numberOfRows && columnIndex<numberOfColumns){
        if(userWord[wordIndex]==puzzleArr[rowIndex][columnIndex]){
            if(wordIndex==lengthOfUserWord-1){
                cout<<"\nWord Found Horizontally Backwards!!\n";
                cout << "Word from ( "<<rowIndex<<","<<columnIndex+lengthOfUserWord-1<<" ) "<<" to ( "<<rowIndex<<","<<columnIndex<<" ) " << endl;
                return;
            }
            else{
                checkHorizontallyBackwards(rowIndex,columnIndex-1,numberOfRows,numberOfColumns,puzzleArr,userWord,wordIndex+1,lengthOfUserWord);
            }
        }
    }
}
void checkVerticallyBackwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord , int wordIndex, int lengthOfUserWord){
    
    if (rowIndex>0 && columnIndex>0 && rowIndex<numberOfRows && columnIndex<numberOfColumns){
        if(userWord[wordIndex]==puzzleArr[rowIndex][columnIndex]){
            if(wordIndex==lengthOfUserWord-1){
                cout<<"\nWord Found Vertically Upwards!!\n";
                cout << "Word from ( "<<rowIndex+lengthOfUserWord-1<<","<<columnIndex<<" ) "<<" to ( "<<rowIndex<<","<<columnIndex<<" ) " << endl;
                return;
            }
            else{
                checkVerticallyBackwards(rowIndex-1,columnIndex,numberOfRows,numberOfColumns,puzzleArr,userWord,wordIndex+1,lengthOfUserWord);
            }
        }
    }
}
void checkVerticallyForwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord , int wordIndex, int lengthOfUserWord){
    
    if (rowIndex>0 && columnIndex>0 && rowIndex<numberOfRows && columnIndex<numberOfColumns){
        if(userWord[wordIndex]==puzzleArr[rowIndex][columnIndex]){
            if(wordIndex==lengthOfUserWord-1){
                cout<<"\nWord Found Vertically Downwards!!\n";
                cout << "Word from ( "<<rowIndex-lengthOfUserWord+1<<","<<columnIndex<<" ) "<<" to ( "<<rowIndex<<","<<columnIndex<<" ) " << endl;
                return;
            }
            else{
                checkVerticallyForwards(rowIndex+1,columnIndex,numberOfRows,numberOfColumns,puzzleArr,userWord,wordIndex+1,lengthOfUserWord);
            }
        }
    }
}
void checkDiagonallyBackwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord , int wordIndex, int lengthOfUserWord){
    
    if (rowIndex>0 && columnIndex>0 && rowIndex<numberOfRows && columnIndex<numberOfColumns){
        if(userWord[wordIndex]==puzzleArr[rowIndex][columnIndex]){
            if(wordIndex==lengthOfUserWord-1){
                cout<<"\nWord Found Diagonally Backwards!!\n";
                cout << "Word from ( "<<rowIndex+lengthOfUserWord-1<<","<<columnIndex+lengthOfUserWord-1<<" ) "<<" to ( "<<rowIndex<<","<<columnIndex<<" ) " << endl;
                return;
            }
            else{
                checkDiagonallyBackwards(rowIndex-1,columnIndex-1,numberOfRows,numberOfColumns,puzzleArr,userWord,wordIndex+1,lengthOfUserWord);
            }
        }
    }
}
void checkDiagonallyForwards(int rowIndex, int columnIndex, int numberOfRows, int numberOfColumns, char**puzzleArr, char *userWord , int wordIndex, int lengthOfUserWord){
    
    if (rowIndex>0 && columnIndex>0 && rowIndex<numberOfRows && columnIndex<numberOfColumns){
        if(userWord[wordIndex]==puzzleArr[rowIndex][columnIndex]){
            if(wordIndex==lengthOfUserWord-1){
                cout<<"\nWord Found Diagonally Forwards!!\n";
                cout << "Word from ( "<<rowIndex-lengthOfUserWord+1<<","<<columnIndex-lengthOfUserWord+1<<" ) "<<" to ( "<<rowIndex<<","<<columnIndex<<" ) " << endl;
                return;
            }
            else{
                checkDiagonallyForwards(rowIndex+1,columnIndex+1,numberOfRows,numberOfColumns,puzzleArr,userWord,wordIndex+1,lengthOfUserWord);
            }
        }
    }
}

#include<iostream>
using namespace std;
void printArray(char **arr, int numberOfRows, int numberOfColumns );
void populateArray(char **arr,  int numberOfRows, int numberOfColumns ); 
void findWord(string combinationSentence);
void checkRowWords(char **arr,  int numberOfRows, int numberOfColumns , int ); 

string dictionary[109] = {
    "cat", "dog", "bat", "hat", "run", "sun", "red", "blue", "pen", "cup",
    "fish", "bird", "rose", "tree", "lake", "moon", "star", "fork", "lamp", "book",
    "play", "pool", "rose", "silk", "song", "ship", "tile", "vest", "wish", "zoom",
    "case", "drop", "face", "gold", "jump", "kick", "lime", "nose", "ring", "tail",
    "cloud", "crawl", "dream", "fresh", "grain", "happy", "juice", "lucky", "music", "piano",
    "queen", "quick", "smile", "storm", "toast", "umbra", "video", "wrist", "zebra", "world",
    "apple", "brave", "chess", "drink", "flame", "grape", "jazz", "lemon", "novel", "pride",
    "quest", "route", "shoe", "trace", "unity", "vivid", "water", "xerox", "yellow", "zesty",
    "silver", "orange", "camera", "travel", "window", "floral", "banana", "purple", "turkey", 
    "magnet", "branch", "guitar", "impact", "castle", "pickle", "forest", "oliver", "planet", "summer",
    "a", "i", "on", "up", "by", "go", "no", "us", "it", "as"
};
int main(){
    int numberOfRows, numberOfColumns;
    cout<<"Enter number of Rows\n";
    cin>>numberOfRows;
    cout<<"Enter number of Columns\n";
    cin>>numberOfColumns;//abcde //abcd //bcde //abc//bcd//cde//ab//bc//de
    
     // Dynamically allocate memory for 2D array
    char** arr = new char*[numberOfRows];
    for (int i = 0; i < numberOfRows; i++) {
        arr[i] = new char[numberOfColumns];
    }    
    populateArray(arr,numberOfRows,numberOfColumns);
    printArray(arr,numberOfRows,numberOfColumns);
    for(int i = 0 ; i < numberOfRows ; i++){
        for(int j = 0 ; j < numberOfColumns ; j++){
            checkRowWords(arr,i,j,numberOfColumns);
        }
    }
     // Deallocate memory for 2D array
    for (int i = 0; i < numberOfRows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}
void populateArray(char **arr,  int numberOfRows, int numberOfColumns ){
    cout<<"Enter Elements of Array: \n";
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            cin >> arr[i][j]; 
        }
    }
}
void printArray(char **arr,  int numberOfRows, int numberOfColumns ){
    for(int i = 0; i < numberOfRows; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            cout<< arr[i][j]<<" "; 
        }
        cout<<endl;
    }
}
void findWord(string combinationSentence){
    for (int i=0 ; i<110;i++){
    if(combinationSentence==dictionary[i]){
        cout<<combinationSentence<<endl;
    }
    }
}
void checkRowWords(char **arr,  int rowNumber, int startingIndex, int numberOfColumns ){
    string combinationSentence = "";
    for(int i=startingIndex ; i<numberOfColumns ;i++){
        combinationSentence+=arr[rowNumber][i];
        findWord(combinationSentence);
    }
}

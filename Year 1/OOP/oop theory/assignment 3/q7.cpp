// Aleena Zahra 23i-2514 BDS-B OOP Assignment 3
#include <iostream>
#include <random>
using namespace std;

class Minesweeper
{
private:
    int **Grid;
    int size;
    int Mines;
    bool **revealedArr;
    bool **flag;
    bool gameOver = false;

public:
    Minesweeper(int size, int mines)
    {
        Mines = mines;
        this->size = size;
        Grid = new int *[size];
        for (int i = 0; i < size; i++)
        {
            Grid[i] = new int[size];
        }
        revealedArr = new bool *[size];
        for (int i = 0; i < size; i++){
            revealedArr[i] = new bool[size];
        }
        flag = new bool *[size];
        for (int i = 0; i < size; i++){
            flag[i] = new bool[size];
        }
        revealedArrInit();
    }
    void revealedArrInit(){
        for(int i=0; i<size ; i++){
            for(int j=0; j<size ; j++){
                revealedArr[i][j]=false;
            }
        }
    }
    ~Minesweeper() {
         for (int i = 0; i < size; i++) {
            delete[] Grid[i];
            delete[] revealedArr[i];
            delete[] flag[i];
        }
        delete[] Grid;
        delete[] revealedArr;
        delete[] flag;
    }
    void fillGridWithMines()
    {
        int minesCount = 0;
        while (minesCount < Mines)
        {
            int row = rand() % size;
            int col = rand() % size;
            if (Grid[row][col] != -1)
            {
                Grid[row][col] = -1;
                minesCount++;
                fillGridWithNeighbours(row, col);
            }
        }
    }
    void fillGridWithNeighbours(int row, int col)
    {
        for (int i = row - 1; i <= row + 1; i++)
        {
            for (int j = col - 1; j <= col + 1; j++)
            {
                if (i >= 0 && i < size && j >= 0 && j < size && !(i == row && j == col))
                {
                    if (Grid[i][j] != -1)
                    {
                        Grid[i][j]++;
                    }
                }
            }
        }
    }
    void reset() {
        //initialize revealed arr to false
        cout<<"\nGame RESET\n";
        revealedArrInit();
        //initialize mines and neighbours
        fillGridWithMines();
        
        
    }
    void revealAll()
    {
        {
            for (int j = 0; j < size; j++)
            {
                cout << "+---";
            }
            cout << "+" << endl;
            for (int i = 0; i < size; i++)
            {

                for (int j = 0; j < size; j++)
                {
                    cout << (Grid[i][j] == -1 ? "| m " : (Grid[i][j] == 0 ? "|   " : "| " + to_string(Grid[i][j]) + " "));
                }
                cout << "|" << endl;

                for (int j = 0; j < size; j++)
                {
                    cout << "+---";
                }
                cout << "+" << endl;
            }
        }
    }
    void revealCell(int row, int col) {
        revealedArr[row][col]=true;
        if(Grid[row][col]==-1){
            revealAll();
            gameOver=true;
            cout<<"YOU STEPPED ON A MINE!!";
            cout<<"Press 0 to to exit game and any other number to restart\n";
            bool restart=false;
            cin>>restart;
            if(restart){
                gameOver=false;
                reset();
            }
        }
        else if(Grid[row][col]==0){
            //revealedArr for all neighbours that arent 0/blank space is also true, and positive numbers in surroungs
            //but not the indexes after the numbers
            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (i >= 0 && i < size && j >= 0 && j < size && !(i == row && j == col) && !revealedArr[i][j]) {
                        revealedArr[i][j]=true;
                        revealCell(i, j);
                    }
                }
            }
        }
        


    }
    bool getGameStatus()
    {
        if (gameOver){
            return true;
        }
        else
            return false;
    }
    void setGameStatus(bool a){
        gameOver=a;
    }
    void flagCell(int row, int col){
        if(revealedArr[row][col]==false){
            if(flag[row][col]==false){
            flag[row][col]=true;
            }
            else{
                flag[row][col]=false;
            }
        }
        
    }
    bool checkWin() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (Grid[i][j] != -1 && !revealedArr[i][j]) {
                return false; 
            }
        }
    }
    return true; 
    }
    void displayGrid(){
        for (int j = 0; j < size; j++){
            cout << "+---";
        }
        cout << "+" << endl;
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (revealedArr[i][j] == true){
                    cout << (Grid[i][j] == -1 ? "| m " : (Grid[i][j] == 0 ? "|   " : "| " + to_string(Grid[i][j]) + " "));
                }
                else{
                    if(flag[i][j]){
                        cout <<"| f " ;
                    }
                    
                    else cout<<"|   ";
                }
            }
            cout << "|" << endl;

            for (int j = 0; j < size; j++){
                cout << "+---";
            }
            cout << "+" << endl;
        }
    }
};

int main(){
    srand(time(nullptr));
    cout << "This program is a minesweeper game on the console\n";
    int gridSize, numOfMines;
    do{
        cout << "Enter n greater than 7 to form an n by n grid:\t";
        cin >> gridSize;
    } while (gridSize < 7);

    cout << "How hard do you want this game to be? 1 being the lowest and " << gridSize << " being the highest? Enter a number:\t";
    cin >> numOfMines;
    while (numOfMines < 1 || numOfMines > gridSize){
        cout << "Pick a number between 1 and " << gridSize << ":\t";
        cin >> numOfMines;
    }
    int row = 0, col = 0;
    char indexStatus;
    Minesweeper minefield(gridSize, numOfMines);
    minefield.fillGridWithMines();
    while (!(minefield.getGameStatus())){
        minefield.displayGrid();
        do{
            cout << "\nENTER ROW:\t";
            cin >> row;
        } while (row < 0 || row > gridSize);
        do{
            cout << "\nENTER COL:\t";
            cin >> col;
        } while (col < 0 || col > gridSize);
        do{
            cout << "PRESS F FOR FLAG, PRESS R FOR REVEAL:\t";
            cin >> indexStatus;
            
        } while (indexStatus != 'r' && indexStatus != 'R' && indexStatus != 'f' && indexStatus != 'F');
        if(indexStatus=='f'||indexStatus=='F'){
                minefield.flagCell(row,col);
            }
        if(indexStatus=='r'||indexStatus=='R'){
                minefield.revealCell(row,col);
                if(minefield.checkWin()){
                    minefield.revealAll();
                    cout<<"\nCONGRATS YOU WINN!!!\n";
                    cout<<"Press 0 to to exit game and any other number to restart\n";
                    bool restart=false;
                    cin>>restart;
                    if(restart){
                        minefield.setGameStatus(false);
                        minefield.reset();
                    }
                }
            }   
        //if a mine or all non mines selected reveal all set bool to true and exit loop
    }
    return 0;
}
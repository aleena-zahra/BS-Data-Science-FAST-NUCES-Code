#include <iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
   int main(){
      srand(time(0));
    int mazerow=0, mazecolumn=0,ghost1row=12,ghost1col=20,ghost2row=5,ghost2col=2,pacmanrow=20,pacmancol=12;
    int i,j,countSpace;
    char maze[25][25];
    char pacmanDirection;



    for(mazerow=0;mazerow<25;mazerow++){
      for(mazecolumn=0;mazecolumn<25;mazecolumn++){

         if( mazerow == 0 || mazecolumn == 0 || mazerow == 24 || mazecolumn == 24 ){
            maze[mazerow][mazecolumn]='#';
         }
        
         else{

            maze[pacmanrow][pacmancol]='>';
            maze[mazerow][mazecolumn]='.';
         }

      }
    }
    //initial maze
    maze[ghost1row][ghost1col]='8';
    maze[ghost2row][ghost2col]='8';
    maze[pacmanrow][pacmancol]='>';
    for(mazerow=0;mazerow<25;mazerow++){
      for(mazecolumn=0;mazecolumn<25;mazecolumn++){
         cout<<maze[mazerow][mazecolumn]<<" ";
      }
      cout<<endl;
    }

    while(true){
      j = rand()%4;
      
      //ghost 2 movement code
      if (j == 0)
      {
         maze[ghost2row][ghost2col]='.';
         ghost2col++;
         
      }
      else
      {
         if (j == 1)
         {
            maze[ghost2row][ghost2col]='.';
            ghost2col--;
         }
         
         else
         {
            if (j == 2)
            {
               maze[ghost2row][ghost2col]='.';
               ghost2row++;
            }
            else
            {
               if (j== 3)
               {
                 maze[ghost2row][ghost2col]='.';
                  ghost2row--;
               }
               
            }
            
            
         }
         
      }
      if(ghost2row != 0 || ghost2row !=24 || ghost2col !=0 || ghost2col !=24)
      maze[ghost2row][ghost2col]='8';
      i = rand()%4;
      
      //ghost movement code
      if (i == 0)
      {
         maze[ghost1row][ghost1col]='.';
         ghost1col++;
      }
      else
      {
         if (i == 1)
         {
            maze[ghost1row][ghost1col]='.';
            ghost1col--;
         }
         
         else
         {
            if (i == 2)
            {
               maze[ghost1row][ghost1col]='.';
               ghost1row++;
            }
            else
            {
               if ( i== 3)
               {
                  maze[ghost1row][ghost1col]='.';
                  ghost1row--;
               }
               
            }
            
            
         }
         
      }
      if(ghost1row != 0 || ghost1row !=24 || ghost1col !=0 || ghost1col !=24)
      maze[ghost1row][ghost1col]='8';

      //pacman direction input
        cout<<endl<<"ENTER < FOR LEFT > FOR RIGHT ^ FOR UP AND v FOR DOWN: ";
        cin>>pacmanDirection;


      //code for where pacman is in the maze
        if (pacmanDirection == 'v')
        {
          pacmanrow++;
          maze[pacmanrow][pacmancol]='v';
          if(pacmanrow>0)
          maze[pacmanrow-1][pacmancol]=' ';
        }
        else
        {
         if (pacmanDirection == '^')
         {
            pacmanrow--;
            maze[pacmanrow][pacmancol]='^';
            if(pacmanrow<24)
            maze[pacmanrow+1][pacmancol]=' ';
         }
         else
         {
            if (pacmanDirection == '<')
            {
               maze[pacmanrow][pacmancol]=' ';
               pacmancol--;
               maze[pacmanrow][pacmancol]='<';
            }
            else
            {
               if (pacmanDirection == '>')
               {
                  maze[pacmanrow][pacmancol]=' ';
                  pacmancol++;
                  maze[pacmanrow][pacmancol]='>';
               }
               
            }
              
         }
         
        }
      //check some conditions
      //if pellets end game over u win
      //if ghost1 or ghost2 coordinates == pacman coordinates game over u lose
       
      //prints maze

      for(mazerow=0;mazerow<25;mazerow++){
         for(mazecolumn=0;mazecolumn<25;mazecolumn++){
          cout<<maze[mazerow][mazecolumn]<<" ";
          if(maze[mazerow][mazecolumn]==' '){
            countSpace++;
            
            }
          
         
         }  
      cout<<endl;
      }
      if(countSpace == 471-3){
            cout<<"/nPacman ate all pellets. YOU WIN! GAME OVER!";
            return 0;
            }
            if(maze[pacmanrow][pacmancol] == maze[ghost1row][ghost1col] || maze[pacmanrow][pacmancol] == maze[ghost2row][ghost2col]){
               cout<<"/nGhost ate Pacman. YOU LOSE! GAME OVER!";
               return 0;
               }
    }

    return 0;
   }

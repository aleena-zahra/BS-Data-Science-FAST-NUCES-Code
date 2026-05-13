/*
Aleena Zahra 
23i-2514 
BDS-B 
Assignment #4
*/ 
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

         if( mazerow == 0 || mazecolumn == 0 || mazerow == 24 || mazecolumn == 24 ) maze[mazerow][mazecolumn]='#';
         
         else if(mazerow == 3 || mazerow == 4){
            if ((mazecolumn>=3 && mazecolumn<=8 )|| (mazecolumn >=16 || mazecolumn<=21)) maze[mazerow][mazecolumn]='#'; }
         
         
         else if(mazecolumn == 4 || mazecolumn == 20){
            if(mazerow >= 8 && mazerow <=16)  maze[mazerow][mazecolumn]='#';}
         
        
         else{

            
            maze[mazerow][mazecolumn]='.';
         }



      }
    }
    maze[pacmanrow][pacmancol]='>';
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
       
      
      //ghost movement code
      if (j == 0)
      {
         maze[ghost2row][ghost2col]='.';
         ghost2col++;
         if ( maze[ghost2row][ghost2col] == '#') ghost2col--;
        
      }
      else
      {
         if (j == 1)
         {
            maze[ghost2row][ghost2col]='.';
            ghost2col--;
            if ( maze[ghost2row][ghost2col] == '#') ghost2col++;
           
         }
         
         else
         {
            if (j == 2)
            {
               maze[ghost2row][ghost2col]='.';
               ghost2row++;
               if( maze[ghost2row][ghost2col]='#') ghost2row--;
              
            }
            else
            {
               if ( j== 3)
               {
                  maze[ghost2row][ghost2col]='.';
                  ghost2row--;
                  if( maze[ghost2row][ghost2col]='#') ghost2row++;
                  
               }
               
            }
            
            
         }
         
      }
    
      maze[ghost2row][ghost2col]='8';

     
      
      //ghost1 movement code
      i = rand()%4;
      if (i == 0)
      {
         maze[ghost1row][ghost1col]='.';
         ghost1col++;
         if ( maze[ghost1row][ghost1col] == '#') ghost1col--;
        
      }
      else
      {
         if (i == 1)
         {
            maze[ghost1row][ghost1col]='.';
            ghost1col--;
            if ( maze[ghost1row][ghost1col] == '#') ghost1col++;
           
         }
         
         else
         {
            if (i == 2)
            {
               maze[ghost1row][ghost1col]='.';
               ghost1row++;
               if( maze[ghost1row][ghost1col]='#') ghost1row--;
              
            }
            else
            {
               if ( i== 3)
               {
                  maze[ghost1row][ghost1col]='.';
                  ghost1row--;
                  if( maze[ghost1row][ghost1col]='#') ghost1row++;
                  
               }
               
            }
            
            
         }
         
      }
      maze[ghost1row][ghost1col]='8';

      //pacman direction input
        cout<<endl<<"ENTER < FOR LEFT > FOR RIGHT ^ FOR UP AND v FOR DOWN: ";
        cin>>pacmanDirection;


      //code for where pacman is in the maze
        if (pacmanDirection == 'v')
        {
          pacmanrow++;
          if ( maze[pacmanrow][pacmancol] == '#') pacmanrow--;

          maze[pacmanrow][pacmancol]='v';
          if(pacmanrow>0)
          maze[pacmanrow-1][pacmancol]=' ';
        }
        else
        {
         if (pacmanDirection == '^')
         {
            pacmanrow--;
            if ( maze[pacmanrow][pacmancol] == '#') pacmanrow++;

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
               if ( maze[pacmanrow][pacmancol] == '#') pacmancol--; 
               maze[pacmanrow][pacmancol]='<';
            }
            else
            {
               if (pacmanDirection == '>')
               {
                  maze[pacmanrow][pacmancol]=' ';
                  pacmancol++;
                  if ( maze[pacmanrow][pacmancol] == '#') pacmancol--; 
                  maze[pacmanrow][pacmancol]='>';
               }
               else 
               cout<<"INVALID INPUT!!!";
               
            }
              
         }
         
        }
      //check some conditions
      //if pellets end game over u win
      //if ghost1 or ghost2 coordinates == pacman coordinates game over u lose
       //clear last maze right before printing maze
        //system("clear");
      //  system("cls");
      //prints maze

      for(mazerow=0;mazerow<25;mazerow++){
         for(mazecolumn=0;mazecolumn<25;mazecolumn++){
          cout<<maze[mazerow][mazecolumn]<<" ";
          if(maze[mazerow][mazecolumn]==' '){
            countSpace++;
            if(countSpace == 471){
            cout<<"Pacman ate all pellets. YOU WIN! GAME OVER!";
            return 0;
            }
            if(maze[pacmanrow][pacmancol] == maze[ghost1row][ghost1col] || maze[pacmanrow][pacmancol] == maze[ghost2row][ghost2col]){
               cout<<"Ghost ate Pacman. YOU LOSE! GAME OVER!";
               return 0;
            }
          }
         
         }  
      cout<<endl;
      }

    }

    return 0;
   }
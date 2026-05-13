#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include <fstream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<string>
#include<unistd.h>
#include<sstream>
#include<cmath>      
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
 // Constants for window size
const int boardWidth = 900;
const int boardHeight = 900;
const int blockSize = 30;
const int blockRadius = 15;
int board[boardHeight][boardWidth];

// Constants for snake properties
int lenghtOfSnake=3;
const int maxSnakeLength = 100;
const float snakeHeadRadius = 15.0;
int snakeMoveinXDirection=0, snakeMoveinYDirection=0;
char snakeDirection='r';
int score=0;
int highScore=425;
int foodX1 = 0, foodY1 = 0, foodX2 = 0, foodY2 = 0, foodX3 = 0, foodY3 = 0, foodX4 = 0, foodY4 = 0, foodX5 = 0, foodY5 = 0;
int superFoodX,superFoodY;
int barrierX1 = 0, barrierY1 = 0, barrierX2 = 0, barrierY2 = 0;
bool foodVisible = false;
bool barrierVisible = false;
bool superFoodVisible = false;
int snakeX[maxSnakeLength] = {400, 370, 340};
int snakeY[maxSnakeLength] = {0,0,0};
bool seeGameHistory=false;
bool wantToSeeHS =false;
bool collisions=false;
bool gameOver = false;
bool Pause = false;
bool startGame = false;
int count = 0;
int lastFoodUpdateTime = 0, lastSuperFoodUpdateTime = 0, lastBarrierUpdateTime = 0;
int level = 1;
char newHighScoreString[30];
char highScoreString[50];
char scoreString[20];
char levelString[10];

void SetCanvasSize(int boardWidth, int boardHeight) {
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, boardWidth, 0, boardHeight+200, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}
 
   void DrawBoard(){
   //draw the screen where the snake is allowed to move  
   DrawSquare( 0, 0 , 900 ,colors[BLUE]);
   }

    void DrawFood(){
    //get time from glut function
     int currentTime = glutGet(GLUT_ELAPSED_TIME);
     
     // if its been more than 15 seconds or the food isnt visible rn (only the first time) then go in loop to get coordinates and then draw the food
    if (!foodVisible ||(currentTime - lastFoodUpdateTime > 15000)) {
   //      generate random numbers and save them as coordinates for the foods, this happens after every 15 secs
          foodX1 = (rand() % (30));
          foodY1 = (rand() % (30));
          foodX2 = (rand() % (30));
          foodY2 = (rand() % (30));
          foodX3 = (rand() % (30));
          foodY3 = (rand() % (30));
          foodX4 = (rand() % (30));
          foodY4 = (rand() % (30));
          foodX5 = (rand() % (30));
          foodY5 = (rand() % (30));
          
          // Check and regenerate if any coordinates are sam
        while ((foodX1 == foodX2) || (foodX1 == foodX3) || (foodX1 == foodX4) || (foodX1 == foodX5) ||
           (foodY1 == foodY2) || (foodY1 == foodY3) || (foodY1 == foodY4) || (foodY1 == foodY5) ||
           (foodX2 == foodX3) || (foodX2 == foodX4) || (foodX2 == foodX5) ||
           (foodY2 == foodY3) || (foodY2 == foodY4) || (foodY2 == foodY5) ||
           (foodX3 == foodX4) || (foodX3 == foodX5) ||
           (foodY3 == foodY4) || (foodY3 == foodY5) ||
           (foodX4 == foodX5) ||
           (foodY4 == foodY5)) {
         //couldve used individual conditions and only generated those that are same but its shorter to write and simpler to explain this way
        foodX1 = (rand() % 30);
        foodY1 = (rand() % 30);
        foodX2 = (rand() % 30);
        foodY2 = (rand() % 30);
        foodX3 = (rand() % 30);
        foodY3 = (rand() % 30);
        foodX4 = (rand() % 30);
        foodY4 = (rand() % 30);
        foodX5 = (rand() % 30);
        foodY5 = (rand() % 30);
    }
          
        //after getting random numbers for coordinates set bool to true to leave loop and reset the update time to current time
        foodVisible = true;
        lastFoodUpdateTime = currentTime;
    }
    //draw the food with the random numbers and align according to  coordinates
    //this i got by trial and error
    //numbers are from 0 to 29 so they represent a single block
    //so we make its coordinates accordingly
     DrawCircle(foodX1 * 30+15, 900 - foodY1 * 30 - 15, 15, colors[RED]);
     DrawCircle(foodX2 * 30 +15, 900 - foodY2 * 30 - 15, 15, colors[RED]);
     DrawCircle(foodX3 * 30+15, 900 - foodY3 * 30 - 15, 15, colors[RED]);
     DrawCircle(foodX4 * 30+15, 900 - foodY4 * 30 - 15, 15, colors[RED]);
     DrawCircle(foodX5 * 30+15, 900 - foodY5 * 30 - 15, 15, colors[RED]);
     
    }
    
     void DrawSuperFood(){
    
    //pretty much the same code for the super food except the time is 1 minute
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
     
    if ( currentTime - lastSuperFoodUpdateTime > 60000) {
        superFoodX = (rand() % (30));
        superFoodY = (rand() % (30));
         
       
        lastSuperFoodUpdateTime = currentTime;
    }
    
    DrawCircle(superFoodX * 30+15, 900 - superFoodY * 30 - 15, 15, colors[YELLOW]);
    }
    
     void DrawSnake() {
    // snake position is such that the block after the head becomes the head
    // and the block after that takes the old position of the block ahead and so on and this keeps happening until the whole lenght of the snake
    for(int i=lenghtOfSnake-1;i>0;i--){
        snakeX[i]=snakeX[i-1];
        snakeY[i]=snakeY[i-1];
    }
    // whatever the direction is the head moves a block. if right it moves ahead, if left is moves back and if up it moves above etc
    if(snakeDirection=='r')  snakeX[0] +=30;
    if(snakeDirection=='l')  snakeX[0] -=30;
    if(snakeDirection=='u')  snakeY[0] +=30;
    if(snakeDirection=='d')  snakeY[0] -=30;

    
    // Drawing the snake head (circle)
    DrawCircle(snakeX[0]+15, snakeY[0]+15, snakeHeadRadius, colors[YELLOW_GREEN]); 
    
    // Drawing the snake body (squares)
     for(int i=1;i<lenghtOfSnake;i++){
     
        DrawSquare(snakeX[i], snakeY[i], blockSize, colors[YELLOW_GREEN]); 
    }
    
    
}
    
    
    void UpdateFood(int foodNumber) {
    //according to what food has been eaten we randomly generate its coordinates again
    
    switch (foodNumber) {
        case 1:
            foodX1 = rand() % 30;
            foodY1 = rand() % 30;
            break;
        case 2:
            foodX2 = rand() % 30;
            foodY2 = rand() % 30;
            break;
        case 3:
            foodX3 = rand() % 30;
            foodY3 = rand() % 30;
            break;
        case 4:
            foodX4 = rand() % 30;
            foodY4 = rand() % 30;
            break;
        case 5:
            foodX5 = rand() % 30;
            foodY5 = rand() % 30;
            break;
         case 6:
            superFoodX = rand() % 30;
            superFoodY = rand() % 30;
            break;
    }
    }
    
    void DrawBarriers(){
    //get time from glut function to check if and then we check if its been 30 secs we change coordinates to new random numbers 
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
     int randomLenght;
     
    if (!barrierVisible || (currentTime - lastBarrierUpdateTime > 30000)) {
    
        
        barrierX1 = rand() % 30;
        barrierY1 = rand() % 30;
        randomLenght = rand() % 30-barrierY1;
        barrierVisible = true;
        lastBarrierUpdateTime = currentTime;
        }
        for(int i=0; i<randomLenght; i +=30){
    DrawSquare( barrierX1*30 +i ,  barrierY1*30, 30, colors[YELLOW]);
         }
    }
    
void Display(){

    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

     glClearColor(0.45, 1, 0.5, 0);
     glClear(GL_COLOR_BUFFER_BIT);   
     
     
     DrawString( 50, 1000, "SNAKE", colors[BLACK]);
    //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
     DrawLine( 150 , 1005 ,  450 , 1005 , 15 , colors[BLACK] );
        if(score!=0){
     DrawLine( 150 , 1005 ,  150+ (score) , 1005 , 15 , colors[YELLOW] );
               }
               //change int to string and concatinate with string 
               sprintf (levelString,"Level: %d ", level); 
               DrawString( 600, 1000, levelString, colors[BLACK]);
               //change int to string and concatinate with string 
               sprintf (scoreString,"Score: %d ", score); 
               DrawString( 800, 1000, scoreString, colors[BLACK]);

      DrawBoard();  
    //to Draw the grid         
    //for(int i=0;i<30;i++){
    //for(int j=0;j<30;j++){
    // DrawSquare(i * 30, 900 - j * 30 - 30, 30, colors[PINK]);}}
     DrawFood();
     DrawSuperFood();
     DrawBarriers();
     DrawSnake();
    
    
     
    //DrawCircle( 200 , 200 , 50 , colors[5]); // This will draw a circle at x=200,y=200 of radius 50
	//                    v1( x,y )   v2( x,y )  , v3( x,y ) 
    //DrawTriangle( 300, 50 , 500, 50 , 400 , 250, colors[MISTY_ROSE] );  // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
    if(!startGame){
             DrawSquare( 0, 0 , 1100 ,colors[BLACK]);
             DrawString( 300, 1000, "dedicated  to  all  snakes  out  there", colors[MISTY_ROSE]);          
             DrawString( 400, 700, "Play", colors[YELLOW]);
             DrawString( 400, 600, "High Score", colors[MISTY_ROSE]);
             DrawString( 400, 500, "Resume", colors[MISTY_ROSE]);
             DrawString( 400, 400, "Press nums 1-5 for Levels", colors[MISTY_ROSE]);
             DrawString( 400, 300, "Game History", colors[MISTY_ROSE]);
             DrawString( 400, 200, "Quit(PLEASE DONT)", colors[MISTY_ROSE]);
    
    // Draw Top squares haha this will take a long timee (took 2 hrs )
    DrawSquare(50, 950, 30, colors[GREEN]);
    DrawSquare(80, 950, 30, colors[GREEN]);
    DrawSquare(110, 950, 30, colors[GREEN]);
    DrawSquare(180, 950, 30, colors[GREEN]);
    DrawSquare(320, 950, 30, colors[GREEN]);
    DrawSquare(455, 950, 30, colors[GREEN]);
    DrawSquare(590, 950, 30, colors[GREEN]);
    DrawSquare(680, 950, 30, colors[GREEN]);
    DrawSquare(770, 950, 30, colors[GREEN]);
    DrawSquare(800, 950, 30, colors[GREEN]);
    DrawSquare(830, 950, 30, colors[GREEN]);

    //draw 2nd
    DrawSquare(50, 920, 30, colors[GREEN]);
    DrawSquare(210, 940, 30, colors[GREEN]);
    DrawSquare(430, 920, 30, colors[GREEN]);
    DrawSquare(650, 920, 30, colors[GREEN]);
    DrawSquare(180, 920, 30, colors[GREEN]);
    DrawSquare(320, 920, 30, colors[GREEN]);
    DrawSquare(480, 920, 30, colors[GREEN]);
    DrawSquare(590, 920, 30, colors[GREEN]);
    DrawSquare(770, 920, 30, colors[GREEN]);

    // Third line 
    DrawSquare(50, 890, 30, colors[GREEN]);
    DrawSquare(80, 890, 30, colors[GREEN]);
    DrawSquare(110, 890, 30, colors[GREEN]);
    DrawSquare(180, 890, 30, colors[GREEN]);
    DrawSquare(240, 910, 30, colors[GREEN]);
    DrawSquare(320, 890, 30, colors[GREEN]);
    DrawSquare(425, 890, 30, colors[GREEN]);
    DrawSquare(455, 890, 30, colors[GREEN]);
    DrawSquare(485, 890, 30, colors[GREEN]);
    DrawSquare(590, 890, 30, colors[GREEN]);
    DrawSquare(620, 890, 30, colors[GREEN]);
    DrawSquare(770, 890, 30, colors[GREEN]);
    DrawSquare(800, 890, 30, colors[GREEN]);

    // Fourth line 
    
    DrawSquare(110, 860, 30, colors[GREEN]);
    DrawSquare(180, 860, 30, colors[GREEN]);
    DrawSquare(260, 870, 30, colors[GREEN]);
    DrawSquare(320, 860, 30, colors[GREEN]);
    DrawSquare(410, 860, 30, colors[GREEN]);
    DrawSquare(500, 860, 30, colors[GREEN]);
    DrawSquare(590, 860, 30, colors[GREEN]);
    DrawSquare(650, 860, 30, colors[GREEN]);
    DrawSquare(770, 860, 30, colors[GREEN]);

    // last line
    DrawSquare(50, 830, 30, colors[GREEN]);
    DrawSquare(80, 830, 30, colors[GREEN]);
    DrawSquare(110, 830, 30, colors[GREEN]);
    DrawSquare(180, 830, 30, colors[GREEN]);
    DrawSquare(290, 840, 30, colors[GREEN]);
    DrawSquare(320, 830, 30, colors[GREEN]);
    DrawSquare(390, 830, 30, colors[GREEN]);
    DrawSquare(520, 830, 30, colors[GREEN]);
    DrawSquare(590, 830, 30, colors[GREEN]);
    DrawSquare(680, 830, 30, colors[GREEN]);
    DrawSquare(770, 830, 30, colors[GREEN]);
    DrawSquare(800, 830, 30, colors[GREEN]);
    DrawSquare(830, 830, 30, colors[GREEN]);
    
     if(wantToSeeHS){
           // DrawHighScoreScreen
         ifstream file("highscore.txt");
         file >> highScore;
         DrawSquare( 0, 0 , 1100 ,colors[PURPLE]);
         sprintf (highScoreString,"The highest score till now is %d ", highScore); 
         DrawString( 350, 600, highScoreString, colors[MISTY_ROSE]);
         DrawString( 400, 200, "Click m for menu", colors[YELLOW]);   
         }
       
       if (seeGameHistory) {
          DrawSquare( 0, 0 , 1100 ,colors[PURPLE]);
          DrawString( 400, 1000, "GAME HISTORY", colors[BLACK]);
          
        
        
    }
         
       }
       
   
    if(gameOver){
    //if gameover bool is true display gameover screen
   DrawSquare(0,0,1100,colors[YELLOW]); 
   if (score>highScore){
             highScore= score;
             ofstream file("highscore.txt");
             file << highScore;
            
    
   sprintf(newHighScoreString, "New Highscore: %d ", highScore);
        DrawString(350, 600, newHighScoreString, colors[RED]);
        }
   else{
    sprintf (scoreString,"score: %d ", score); 
         DrawString( 350, 600, scoreString, colors[RED]);
   }
   
   DrawString( 352,500,"GAME OVER :(",colors[RED]); 
   DrawString( 349,700,"Press P to play again",colors[BLUE]);
    }
   

   glutSwapBuffers(); // do not modify this line..
   
   
}


/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard                                                              
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {s
    
    /*if the direction entered by the user is
    left/right/up/down and the snake isnt already moving right,left,down,up
    the snake moves a block behind,ahead,above,below 
    */
    if (key == GLUT_KEY_LEFT  ) {
      if(snakeDirection!='r'){
      snakeDirection = 'l';
      snakeMoveinXDirection -=30;
      }
      
    } else if (key == GLUT_KEY_RIGHT  ) {
       if(snakeDirection!='l'){
         snakeDirection = 'r';
         snakeMoveinXDirection +=30;
        }		
    } else if (key == GLUT_KEY_UP)  {
        if(snakeDirection!='d'){
         snakeDirection = 'u';
         snakeMoveinYDirection += 30;
        }
        
    }
    else if (key == GLUT_KEY_DOWN)  {
        if(snakeDirection!='u'){
          snakeDirection = 'd';
          snakeMoveinYDirection -=30;
        }
   		
    
    }

    
    //to redraw
     glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC || key == 'q' || key == 'Q') {
        exit(1); 
    }
    /*if p is pressed the game plays so the menu screen or gameover screen goes away
    the level and score and lenght of snake reset
    */
    if (int(key) == 'r'){  
    startGame=true;
    }
    if (int(key) == 'p'){  
    startGame=true;
    gameOver=false;
    level=1;
    score=0;
    lenghtOfSnake=3;
    }
    //m displays menu by turning bool false
    else if (int(key) == 'm'){  
    startGame=false;
    wantToSeeHS=false;
    seeGameHistory=false;
    }
    else if (int(key) == 'h'){  
    wantToSeeHS=true;
    }
     if (int(key) == 'H'){  
    seeGameHistory=true;
    
    }
    
    // to manually switch levels using keys, each time levels are changed lenght of snake, level and score are reset
    else if (int(key) == '1'){ 
    startGame=true; 
    level=1;
    score=0;
    lenghtOfSnake=3;
    }
    else if (int(key) == '2'){  
    startGame=true;  
    level=2;
    score=0;
    lenghtOfSnake=3;
    }
    else if (int(key) == '3'){  
    startGame=true;  
    level=3;
    score=0;
    lenghtOfSnake=3;
    }
    else if (int(key) == '4'){  
    startGame=true;  
    level=4;
    score=0;
    lenghtOfSnake=3;
    }
    else if (int(key) == '5'){  
    startGame=true;  
    level=5;
    score=0;
    lenghtOfSnake=3;
    }
    if (key == 'g'  ) {gameOver=true;}
    //a s w d keys to move the snake, just like the arrow keys
     if (key == 'a'  ) {
      if(snakeDirection!='r'){
      snakeDirection = 'l';
      snakeMoveinXDirection -=30;
      }
      
    } else if (key == 'd'  ) {
       if(snakeDirection!='l'){
         snakeDirection = 'r';
         snakeMoveinXDirection +=30;
        }		
    } else if (key == 'w')  {
        if(snakeDirection!='d'){
         snakeDirection = 'u';
         snakeMoveinYDirection += 30;
        }
        
    }
    else if (key == 's')  {
        if(snakeDirection!='u'){
          snakeDirection = 'd';
          snakeMoveinYDirection -=30;
        }
        } 
    
    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
    void snakeMovement(){

    
   //snake comes back from the other side
   // note a problem here at the top of the screen that idk how to fix yet
   if (snakeY[0] >=870)  snakeY[0] = 0;
   else if (snakeY[0] <0)      snakeY[0] = 870;
   else if (snakeX[0] >=900)  snakeX[0] = 0;  
   else if (snakeX[0] <0)      snakeX[0] = 870;
   
    }

   void FoodLogic(){

      // if the food x and y coordinates (BOTH ) are the same as the snake x and y coordinates that means that the score increases and the food coordinates change and also the bar at the top is changed
      
     // we insert an int into update food function, that number signifies what food has been eaten, where super food is 6
       if(   (900-foodY1*30-15 == snakeY[0]+15 )  &&     (foodX1* 30+15 == snakeX[0] +15)    ) {
          score +=5;  
          //we take the score variable and change it to int and store its value in scoreString
          sprintf(scoreString,"score: %d ", score); 
        lenghtOfSnake++;
        UpdateFood(1);
        glutPostRedisplay();
       }
       if(   (900-foodY2*30-15 == snakeY[0] +15)  &&     (foodX2* 30+15 == snakeX[0] +15)    )  {
       score +=5;  
        sprintf (scoreString,"score: %d ", score);   
        lenghtOfSnake++;
        UpdateFood(2);
        glutPostRedisplay();
       }
       if(    (900-foodY3*30-15 == snakeY[0] +15)  &&     (foodX3* 30+15 == snakeX[0] +15)    ) {
        score +=5;  
        sprintf (scoreString,"score: %d ", score); 
        lenghtOfSnake++;
        UpdateFood(3);
        glutPostRedisplay();
       }
       if(    (900-foodY4*30-15 == snakeY[0] +15)  &&    (foodX4* 30+15 == snakeX[0] +15)    )  {
        score +=5;  
        sprintf (scoreString,"score: %d ", score); 
        lenghtOfSnake++;
        UpdateFood(4);
        glutPostRedisplay();
       }
       if(    (900-foodY5*30-15 == snakeY[0] +15)  &&     (foodX5* 30+15 == snakeX[0] +15)    ) {
        score +=5;  
        sprintf (scoreString,"score: %d ", score); 
        lenghtOfSnake++;
        UpdateFood(5);
        glutPostRedisplay();
        }
        if(    (900-superFoodY*30-15 == snakeY[0] +15)  &&     (superFoodX* 30+15 == snakeX[0] +15)    ) {
        score +=20;  
        sprintf (scoreString,"score: %d ", score); 
        lenghtOfSnake++;
        UpdateFood(6);
        glutPostRedisplay();
        }    
    }
    
    bool gameEnds() {
    
    bool collision=false;
    // if the snake head coordinates are equal to another snake coordinate then the game must end
    for (int i = 1; i < lenghtOfSnake; i++) {
        if ((snakeX[0] + 15 == snakeX[i]) && (snakeY[0] + 15 == snakeY[i])) {
            collision = true;
            break;
        }
    }
    // if the snakes head coordinates are equal to the barrier coordinates then the game must end
    for (int i = 1; i <= 3; i *= 30) {
        if ((snakeX[0] + 15 == barrierX1 * 30 + i) && (snakeY[0] + 15 == barrierY1 * 30)) {
            collision = true;
            break;
        }
    }

    if (collision) {
        gameOver = true;
        glutPostRedisplay();
    }

    return gameOver;
}

    

   void logic(){
          
          snakeMovement();
          
          //Game Over Logic
          // if the snake head coordinates are equal to another snake coordinate then the game must end
           for(int i=1; i<lenghtOfSnake; i++){
              if((snakeX[0] + 15 == snakeX[i]) || (snakeY[0] +15 == snakeY[i])) {
                    gameOver=true;
                    glutPostRedisplay();
                 }
            }
       // if the snakes head coordinates are equal to the barrier coordinates then the game must end
       for(int i=1;i<=3; i *=30){
       if ( (snakeX[0] + 15 == barrierX1*30 + i) && (snakeY[0] + 15== barrierY1*30) ){
       gameOver= true;
        glutPostRedisplay();
        
        }
       }
          FoodLogic();
      
           if (score>300 && level<5){ 
             level++;
             score=0;
             lenghtOfSnake=3;
             sprintf (levelString,"level: %d ", level);   
             
             }
             else{
             if (lenghtOfSnake > maxSnakeLength){
             lenghtOfSnake=maxSnakeLength;
             }
             
             }
             
          }
          
   void Timer(int m) {
   
    logic();
    glutPostRedisplay();
    glutTimerFunc(1000.0 / (FPS*level), Timer, 0);
}



int main(int argc, char*argv[]) {
    
    InitRandomizer(); 
    glutInit(&argc, argv); 

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowPosition(50, 50); 
    glutInitWindowSize(1000, 1000); 
    glutCreateWindow("aleena's snake game"); 
    SetCanvasSize(boardWidth, boardHeight); 
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
   
   // calls inputs 
    glutSpecialFunc(NonPrintableKeys); 
    glutKeyboardFunc(PrintableKeys); 
    logic(); //game's logic
   
    glutTimerFunc(1000.0 / FPS, Timer, 0);

    glutMainLoop();
    return 1;
}
    
#endif 


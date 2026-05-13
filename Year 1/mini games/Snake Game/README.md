# Snake Game

This is a simple snake game implemented in C++ using OpenGL. The game allows players to control a snake, moving it around the screen to eat food and grow longer. However, players must avoid collisions with barriers and their own snake body. The game features multiple levels and keeps track of the player's score.
## Screenshots
## Menu 
![Screenshot from 2024-06-08 11-07-26](https://github.com/aleena-zahra/snake-game-cpp/assets/155615101/8cea4b23-6117-46f9-9163-9774ed8f9d0c)

## Game Screen
![Screenshot from 2024-06-08 11-08-34](https://github.com/aleena-zahra/snake-game-cpp/assets/155615101/299e76fd-37bc-40e7-9227-2887cede31c2)

## Instructions

- Use the arrow keys (up, down, left, right) or the keys 'w', 'a', 's', 'd' to control the movement of the snake.
- Press 'p' to start the game or resume after a game over.
- Press 'm' to go back to the main menu.
- Press 'h' to view the high score.
- Press 'H' to view game history.
- Press '1', '2', '3', '4', or '5' to manually switch levels.
- Press 'q' or 'ESC' to quit the game.

## Features

- 5 levels with increasing difficulty.
- Dynamic food generation with different types of food.
- High score tracking.
- Game history tracking.
- Barrier obstacles to avoid collision.
- Smooth animation and gameplay.

## How to Run
I made this on Ubuntu so I only know how to run it there:

1. Clone this repository to your local machine by clicking on code and downloading the zip folder.

2. Install GCC (g++) compiler:
   
```
sudo apt-get install g++
```

3. Install Libraries like OpenGL and glut
   
```
sudo apt-get install freeglut3-dev glew-utils libglew-dev libfreeimage-dev
```

4. Run Make File
   To run this project, you must compile it first. To do so, go to the root of the project folder via terminal and run the following:
   
```
make
```

5. Run the executable file generated, 'gamerelease' , by clicking on it.

## Credits

This game was solely developed by me (Aleena Zahra) for my first semester final project.

## Notes

- The game is optimized for a canvas size of 900x900 pixels.
- Adjustments can be made to the code for customization or further development.
- For any issues or feedback, please open an issue on GitHub.

Enjoy playing the game! 🐍🎮

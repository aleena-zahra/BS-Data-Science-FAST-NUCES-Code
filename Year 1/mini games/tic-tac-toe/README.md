# Tic Tac Toe Game - Model View Controller (MVC) Implementation

This repository contains my first-ever implementation of the Model-View-Controller (MVC) design pattern using Python and the Turtle graphics library. 
In this project I aimed to create a simple but interactive Tic Tac Toe game implementation while learning MVC architectural pattern. 
The MVC pattern separates the application into three interconnected components: Model, View, and Controller. Here's a brief overview of each component:

**Model:**
The Model represents the core functionality and data of the application. 
It encapsulates the game logic and state, providing methods for updating the game board, checking for a win or tie, and making moves.
**View:** 
The View component is responsible for the user interface and presentation of the game. 
It utilizes the Turtle graphics library to draw the game board, grid, player marks (X and O), and display game-related messages.

**Controller:** 
The Controller acts as an intermediary between the Model and View components. 
It handles user input, such as mouse clicks on the game board, and invokes appropriate methods in the Model to update the game state. 
Additionally, it interacts with the View to display game outcomes and win and tie messages.
## Screenshots
![cross](https://github.com/aleena-zahra/tic-tac-toe-python-turtle/assets/155615101/ab473f9c-9232-44ec-a098-d8711d5a5c59)
![win](https://github.com/aleena-zahra/tic-tac-toe-python-turtle/assets/155615101/baafd9df-68e9-4b8f-a06f-c120dcb8012f)


## Features

- Interactive Tic Tac Toe gameplay.
- User-friendly interface using Turtle graphics.
- MVC architecture for better code organization and separation of concerns.
- Win detection for rows, columns, and diagonals.
- Tie detection when all cells are filled.
- Flexible code writing
## Usage

To play the Tic Tac Toe game, simply run the `view.py` file. Click on any of the nine grid cells to place your mark (X or O). 
The game will automatically detect wins, ties, and switch between players.

## Repository Structure

- `view.py`: The main entry point of the application. It initializes the game window and sets up event listeners for mouse clicks.
  
- `controller.py`: The Controller component of the MVC architecture. It handles user input and communicates with the Model and View components.
  
- `model.py`: The Model component responsible for the game logic and state. It includes functions for updating the game board, checking win conditions, and determining game outcomes.
  
- `README.md`: This file, providing an overview of the project and instructions for usage.

## Dependencies

- Python 3.x
- Turtle graphics library
## End Note
I hope you have fun discovering my game. This was a fun project to work on and I learned to apply some of my coding skills while increasing my logic building skills.
This project was a fun way for me to learn MVC Architecture. I hope you like my implementation. Cheers!

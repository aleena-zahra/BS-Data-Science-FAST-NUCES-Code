# 🧱 Brick Breaker Game ![GIF](https://emojis.slackmojis.com/emojis/images/1531849430/4246/blob-sunglasses.gif?1531849430)

Made with C++ and GLUT  
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)


Welcome to the **Brick Breaker Game** — a c++ oop remake of the classic arcade hit! Use your paddle to keep the ball alive, break through brick walls, and unleash power-ups. Every level throws something new at you — are you ready?

## Table of Contents

- [Screenshots](#screenshots)
- [Features](#features)
- [Installation](#installation)
- [Gameplay](#gameplay)
- [Classes and Structure](#classes-and-structure)
- [Power-ups](#power-ups)
- [Bricks](#bricks)
- [Contributing](#contributing)
- [License](#license)

## Level 1
![Screenshot from 2024-06-08 10-42-01](https://github.com/aleena-zahra/Brick-Breaker-Cpp/assets/155615101/593887d7-4b5f-4d7d-b1be-984b7bf84ad7)
## Level 2
![Screenshot from 2024-06-08 10-42-11](https://github.com/aleena-zahra/Brick-Breaker-Cpp/assets/155615101/954156a1-b9ef-46d7-87b8-b5e30498ecac)
## Level 3
![Screenshot from 2024-06-08 10-41-26](https://github.com/aleena-zahra/Brick-Breaker-Cpp/assets/155615101/ec215585-3b95-48bd-960a-6b638eac0d7f)
## Powerups and changing ball and paddle color
![Screenshot from 2024-06-08 10-46-08](https://github.com/aleena-zahra/Brick-Breaker-Cpp/assets/155615101/07c08740-24e9-44be-82d5-d448b0aba43f)


## ✨ Features

- Classic brick-breaking gameplay with modern visuals
- Multiple power-ups:
  - 🚀 Speed boost
  - 🐢 Speed slow
  - 🧱 Paddle grow/shrink
- Bricks with different strengths and hidden effects
- Score tracking & lives system
- Smooth mouse-controlled paddle


## Installation
To get the game up and running, follow these steps:

1. **Clone the repository:**
    ```sh
    git clone https://github.com/aleena-zahra/Brick-Breaker-Cpp.git
    cd Brick-Breaker-Cpp
    ```

2. **Install dependencies:**
    Ensure you have a C++ compiler and the necessary graphics libraries installed. This game uses a custom graphics library (`util.h`), along with Glut Library
   ```sh
   sudo apt install freeglut3 freeglut3-dev
   sudo apt install build-essential libx11-dev libxmu-dev libxi-dev libglu1-mesa libglu1-mesa-dev
   ```

4. **Compile the game:**
    ```sh
    make
    ```

5. **Run the game:**
    ```sh
    ./game
    ```

## 🕹 Gameplay
- 🖱 Move the paddle using your mouse
- 🧱 Break all bricks to advance to the next level
- 💥 Collect power-ups falling from broken bricks
- ❤️ Don’t let the ball fall — lives are limited!

## Contributing
Contributions to enhance the game are welcome! To contribute:
1. Fork the repository.
2. Create a new branch.
3. Make your changes and commit them.
4. Push your changes to your fork.
5. Submit a pull request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

Enjoy playing the Breakout Game! If you have any questions or feedback, feel free to open an issue on the repository.


# 2d_Platformer
Welcome to the 2D Platformer Game! This game is developed using SDL2 in C++ and Visual Studio Code. In this game, you will navigate a character through various levels, avoiding obstacles and enemies, collecting power-ups, and aiming to reach the end goal.

# Features

Player Movement: Smooth and responsive controls for moving the player left, right, and jumping.

Camera Movement: The camera follows the player, ensuring the player remains in the center of the screen as much as possible.

Collision Detection and Damage: Accurate collision detection with platforms, enemies, and other objects. The player takes damage upon colliding with enemies.

Health Bar Control: A health bar that decreases when the player takes damage and can be replenished with power life pickups.

Power Life Pickup: Collectible hearts that increase the player's current health.

Start Screen: A start screen that welcomes players and provides options to start the game or view instructions.

Game Over Screen: A game over screen that appears when the player loses all their health, with an option to restart the game.

Game Win Screen: A game win screen that appears when the player completes all levels, celebrating their success.

Sounds: Various sound effects for player actions, collisions, and game events to enhance the gaming experience.

# Installation

1. Ensure you have SDL2 installed on your system. You can download it from SDL's official website.

2. Clone this repository to your local machine using: git clone https://github.com/your-username/2D_Platformer_Game.git

3. Open the project in VS code.

4. To compile, run the following command in your terminal: g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

5. Then, run the executable: ./a.exe

# How to Play
Start the Game: On the start screen, press the "Start" button to begin the game.

Navigate Levels: Use the arrow keys to move and the spacebar to jump. Avoid enemies and obstacles.

Collect Power-up: Pick up heart icons to replenish your health.

Complete Level: Reach the end of each level to progress to the next.

Game Over: If you lose all your health, the game over screen will appear. You can choose to restart the game.

Win the Game: Complete all levels to reach the game win screen and celebrate your victory!


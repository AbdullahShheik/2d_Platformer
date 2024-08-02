#include "SDL.h"
#include "SDL_image.h"
#include "RenderWindow.hpp"
#include "player.hpp"
#include "Platform.hpp"
#include "SDL_mixer.h"
#include "utils.hpp"
#include "camera.hpp"
#include "enemy.hpp"
#include "GameOver.hpp"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Check for intersection between two SDL_Rect
bool hasIntersection(const SDL_Rect &a, const SDL_Rect &b)
{
    // different ground levels
    if (((a.y - b.y) == 100) && (!(a.x + a.w <= b.x || a.x >= b.x + b.w)))
    {
        return true;
    }
    // Check horizontal overlap
    if (a.x + a.w <= b.x || a.x >= b.x + b.w)
    {
        return false;
    }
    // Check vertical overlap
    if (a.y + a.h <= b.y || a.y >= b.y + b.h)
    {
        return false;
    }

    return true;
}

int main(int argc, char *args[])
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
    { // Initialize SDL audio
        cout << "SDL_Init failed: " << SDL_GetError() << endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cout << "IMG_Init failed: " << IMG_GetError() << endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    { // Initialize SDL_mixer
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return 1;
    }

    RenderWindow window("Game v1.0", 1280, 720);
    int windowRefreshRate = window.getRefreshRate();

    // Load textures
    SDL_Texture *playerTexture = window.loadTexture("assets/hulking_knight.png");
    SDL_Texture *enemyTexture = window.loadTexture("assets/enemy.png");
    SDL_Texture *enemy2Texture = window.loadTexture("assets/enemy3.png");
    SDL_Texture *grassTexture = window.loadTexture("assets/ground_grass_1.png");
    SDL_Texture *bgTexture = window.loadTexture("assets/background.jpeg");
    SDL_Texture *startScreenTexture = window.loadTexture("assets/StartScreen.jpg");
    SDL_Texture *gameOverTexture = window.loadTexture("assets/GameOver.jpg");
    SDL_Texture *finishLineTexture = window.loadTexture("assets/finishFlag.png");
    SDL_Texture *winningScreenTexture = window.loadTexture("assets/YouWin.jpg");
    SDL_Texture *powerLifeTexture = window.loadTexture("assets/playerHealth.png");

    if (playerTexture == NULL || grassTexture == NULL || bgTexture == NULL || startScreenTexture == NULL || gameOverTexture == NULL)
    {
        cout << "Failed to load texture: " << IMG_GetError() << endl;
        return 1;
    }

    Mix_Music *startScreenMusic = Mix_LoadMUS("assets/StartScreen_Audio.mp3");
    if (startScreenMusic == NULL)
    {
        cout << "Failed to load start screen music! SDL_mixer Error: " << Mix_GetError() << endl;
    }

    Mix_Music *damageSound = Mix_LoadMUS("assets/DamageSound.mp3");
    if (damageSound == NULL)
    {
        cout << "Failed to load damage sound! SDL_mixer Error: " << Mix_GetError() << endl;
    }

    Mix_Music *gameOverSound = Mix_LoadMUS("assets/gameover_sound.mp3");
    if (gameOverSound == NULL)
    {
        cout << "Failed to load game over sound! SDL_mixer Error: " << Mix_GetError() << endl;
    }

    Mix_Music *winMusic = Mix_LoadMUS("assets/WinSound.mp3");
    if (!winMusic)
    {
        SDL_Log("Failed to load MP3 file: %s", Mix_GetError());
    }

    Mix_Music *PickLifeMusic = Mix_LoadMUS("assets/LifePickSound.mp3");
    if (!winMusic)
    {
        SDL_Log("Failed to load MP3 file: %s", Mix_GetError());
    }

    // Create player and enemy
    Player player(Vector2f(100, 100), playerTexture);
    Enemy enemy(Vector2f(499, 100), enemyTexture);
    Enemy enemy2(Vector2f(1450, 100), enemy2Texture);

    // Create background entity
    Entity background(Vector2f(0, 0), bgTexture);
    background.setSize(2560, 720);

    // Create platforms (grass textures at the bottom)
    int grassWidth, grassHeight;
    SDL_QueryTexture(grassTexture, NULL, NULL, &grassWidth, &grassHeight);

    // Create Camera
    Camera camera(Vector2f(0, 0), 1280, 720, 2560, 720);

    // Create finish Line
    finishLine finish(2350, 500, 200, 200, finishLineTexture);

    // create powerLife
    PowerLife powerLife(1300, 600, powerLifeTexture);

    std::vector<Platform> platforms;
    int numTexturesX = ceil(2560.0 / grassWidth);
    for (int i = 0; i < numTexturesX; ++i)
    {
        platforms.push_back(Platform(Vector2f(i * grassWidth, 720 - grassHeight), grassTexture));
    }

    bool gameRunning = true;
    bool gameStarted = false;
    bool gameOver = false;
    bool gameWon = false;
    SDL_Event event;

    GameOver gameOverHandler;

    Mix_PlayMusic(startScreenMusic, -1);

    // Display the starting screen
    while (!gameStarted && gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                gameStarted = true;
                Mix_HaltMusic();
            }
        }

        window.clear();
        window.renderStartScreen(startScreenTexture); // Render the start screen
        window.display();
    }

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeSeconds();

    while (gameRunning)
    {
        int startTicks = SDL_GetTicks();
        float newTime = utils::hireTimeSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;

        bool isColliding = false;
        bool isColliding_ = false;

        while (accumulator >= timeStep)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    gameRunning = false;
                }
                if (gameStarted && !gameOver && !gameWon)
                {
                    player.handleInput(event);
                }
                else if (gameOver || gameWon)
                {
                    gameOverHandler.handleGameOver(event, gameRunning, gameStarted, gameOver, player, enemy, powerLife, camera);
                }
            }

            player.update(timeStep);
            if (player.getHealth() == 0)
            {
                gameOver = true;
            }

            enemy.update(timeStep);
            enemy2.update2(timeStep);
            camera.update(player.getPos());
            accumulator -= timeStep;

            SDL_Rect playerRect = {player.getPos().x, player.getPos().y, player.getCurrentFrame().w, player.getCurrentFrame().h};
            SDL_Rect enemyRect = {enemy.getPos().x, enemy.getPos().y, enemy.getCurrentFrame().w, enemy.getCurrentFrame().h};
            SDL_Rect enemyRect_ = {enemy2.getPos().x, enemy2.getPos().y, enemy2.getCurrentFrame().w, enemy2.getCurrentFrame().h};

            isColliding = hasIntersection(playerRect, enemyRect);
            isColliding_ = hasIntersection(playerRect, enemyRect_);

            if (isColliding)
            {
                Mix_PlayMusic(damageSound, 1);
                player.reduceHealth(20);
                player.setColorMod(playerTexture, 255, 0, 0);

                Vector2f playerVelocity = player.getVelocity();
                playerVelocity.x = -playerVelocity.x; // Reverse direction
                Vector2f newPos = player.getPos();
                newPos.x += playerVelocity.x * 0.2f; // Move slightly in the opposite direction
                player.setPos(newPos);               // Set the new position

                player.setVelocity(playerVelocity);

                player.handleCollision();
                player.setInCollision(true);
            }
            else
            {
                player.resetColorMod(playerTexture);
                player.setInCollision(false);
            }

            if (isColliding_)
            {
                Mix_PlayMusic(damageSound, 1);
                player.reduceHealth(20);
                player.setColorMod(playerTexture, 255, 0, 0);

                Vector2f playerVelocity = player.getVelocity();
                playerVelocity.x = -playerVelocity.x; // Reverse direction
                Vector2f newPos = player.getPos();
                newPos.x += playerVelocity.x * 0.2f; // Move slightly in the opposite direction
                player.setPos(newPos);               // Set the new position

                player.setVelocity(playerVelocity);

                player.handleCollision();
                player.setInCollision(true);
            }
            else
            {
                player.resetColorMod(playerTexture);
                player.setInCollision(false);
            }

            if (hasIntersection(playerRect, finish.position))
            {
                gameWon = true;
                if (Mix_PlayMusic(winMusic, 1) == -1)
                {
                    SDL_Log("Failed to play win sound: %s", Mix_GetError());
                }
            }

            if (hasIntersection(playerRect, powerLife.getCollisionBox()))
            {
                if (Mix_PlayMusic(PickLifeMusic, 1) == -1)
                {
                    SDL_Log("Failed to play win sound: %s", Mix_GetError());
                }

                player.increaseHealth(20);
                powerLife = PowerLife(-100, -100, powerLifeTexture); // Move off-screen
            }
        }

        window.clear();

        if (gameStarted && !gameOver && !gameWon)
        {
            // Render the background entity
            window.renderBackground(background, camera.getCameraOffset());

            // Render platforms
            for (Platform &plat : platforms)
            {
                window.renderPlatform(plat, camera.getCameraOffset());
            }

            // Render player
            window.render(player, camera.getCameraOffset());

            // Render enemy
            window.render(enemy, camera.getCameraOffset());

            // render enemy2
            window.render(enemy2, camera.getCameraOffset());

            // Render player's health bar
            window.renderHealthBar(player.getHealth(), camera.getCameraOffset());

            // render finish line
            window.renderFinishLine(finish, camera.getCameraOffset());

            // get powerLife
            window.renderPowerLife(powerLife, camera.getCameraOffset());
        }
        else if (gameOver)
        {
            SDL_Rect src = {0, 0, 1280, 720};
            SDL_Rect dst = {0, 0, 1280, 720};
            window.renderTexture(gameOverTexture, &src, &dst);
            gameOverHandler.handleGameOver(event, gameRunning, gameStarted, gameOver, player, enemy, powerLife, camera);

            if (!gameRunning || !gameOver)
            {
                Mix_HaltMusic();
            }
        }
        else if (gameWon)
        {
            SDL_Rect src = {0, 0, 1280, 720};
            SDL_Rect dst = {0, 0, 1280, 720};
            window.renderTexture(winningScreenTexture, &src, &dst);
            gameOverHandler.handleGameOver(event, gameRunning, gameStarted, gameOver, player, enemy, powerLife, camera);

            if (!gameRunning || !gameWon)
            {
                Mix_HaltMusic();
            }
        }

        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < 1000 / window.getRefreshRate())
        {
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
        }
    }

    window.cleanUP();
    Mix_FreeMusic(startScreenMusic);
    Mix_FreeMusic(gameOverSound);
    Mix_FreeMusic(damageSound);
    Mix_FreeMusic(winMusic);

    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyTexture(grassTexture);
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyTexture(startScreenTexture);
    SDL_DestroyTexture(gameOverTexture);
    SDL_DestroyTexture(winningScreenTexture);

    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

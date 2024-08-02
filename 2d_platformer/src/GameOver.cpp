#include "GameOver.hpp"
#include "SDL.h"
#include "Player.hpp"
#include "Enemy.hpp"
#include "SDL_mixer.h"
#include "Camera.hpp"

void GameOver::handleGameOver(SDL_Event &event, bool &gameRunning, bool &gameStarted, bool &gameOver, Player &player, Enemy &enemy, PowerLife &powerLife, Camera &camera) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_q) {
            gameRunning = false;
            Mix_HaltMusic();
        } else if (event.key.keysym.sym == SDLK_r) {
            // Reset game state
            gameStarted = true;
            gameOver = false;

            player.setHealth(100); // Reset player's health
            player.setPos(Vector2f(100, 100)); // Reset player's position
            player.setVelocity(Vector2f(0, 0)); // Reset player's velocity

            enemy.setPos(Vector2f(499, 100)); // Reset enemy's position
            enemy.setVelocity(Vector2f(0, 0)); // Reset enemy's velocity

            powerLife = PowerLife(1300, 600, powerLife.getTexture()); // Reset power life position

            camera.setPos(Vector2f(0, 0)); // Reset camera position
            Mix_HaltMusic();
        }
    }
}

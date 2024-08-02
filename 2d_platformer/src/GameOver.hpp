#pragma once
#include "SDL.h"
#include "Player.hpp"
#include "Enemy.hpp"
#include "PowerLife.hpp"
#include "Camera.hpp"

class GameOver {
public:
    void handleGameOver(SDL_Event &event, bool &gameRunning, bool &gameStarted, bool &gameOver, Player &player, Enemy &enemy, PowerLife &powerLife, Camera &camera);
};

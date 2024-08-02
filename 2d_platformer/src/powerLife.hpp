#pragma once

#include "SDL.h"
#include "math.hpp"

class PowerLife {
public:
    PowerLife(int x, int y, SDL_Texture* texture);
    void renderPower(SDL_Renderer* renderer, Vector2f cameraOffSet);
    SDL_Rect getCollisionBox();
    SDL_Texture* getTexture();

private:
    SDL_Rect collisionBox;
    SDL_Texture* texture;
};
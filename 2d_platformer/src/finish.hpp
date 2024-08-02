#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "math.hpp"

class finishLine
{
    public:
        SDL_Rect position; 
        SDL_Texture* texture;

        finishLine(int x, int y, int width, int height, SDL_Texture* tex);
        void render(SDL_Renderer* renderer, Vector2f cameraOffset);

};
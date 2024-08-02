#pragma once

#include "SDL.h"
#include "math.hpp"

class Entity {
public:
    Entity(Vector2f pos, SDL_Texture* tex);
    Vector2f& getPos();
    void setPos(const Vector2f& p_pos);

    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
    void setSourceRect(int x, int y, int w, int h);
    void setSize(int w, int h);
private:
    Vector2f pos;
    SDL_Texture* tex;
    SDL_Rect currentFrame;
};

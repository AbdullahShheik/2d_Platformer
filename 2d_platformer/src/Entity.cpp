#include "Entity.hpp"

Entity::Entity(Vector2f pos, SDL_Texture* tex)
    : pos(pos), tex(tex) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 64; 
    currentFrame.h = 64; 
}

Vector2f& Entity::getPos() {
    return pos;
}

SDL_Texture* Entity::getTex() {
    return tex;
}

SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}

void Entity::setSourceRect(int x, int y, int w, int h) {
    currentFrame.x = x;
    currentFrame.y = y;
    currentFrame.w = w;
    currentFrame.h = h;
}

void Entity::setSize(int w, int h) {
    currentFrame.w = w;
    currentFrame.h = h;
}

void Entity::setPos(const Vector2f& p_pos)
{
    pos = p_pos;
}
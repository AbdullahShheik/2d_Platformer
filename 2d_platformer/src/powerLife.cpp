#include "powerLife.hpp"

PowerLife::PowerLife(int x, int y, SDL_Texture* texture) {
    this->texture = texture;
    collisionBox = { x, y, 100, 100 }; 
}

void PowerLife::renderPower(SDL_Renderer* renderer, Vector2f cameraOffset) {
    SDL_Rect renderRect = { collisionBox.x - cameraOffset.x, collisionBox.y - cameraOffset.y, collisionBox.w, collisionBox.h };
    SDL_RenderCopy(renderer, texture, nullptr, &renderRect);
    
}

SDL_Rect PowerLife::getCollisionBox() {
    return collisionBox;
}

SDL_Texture* PowerLife::getTexture()
{
    return texture;
}
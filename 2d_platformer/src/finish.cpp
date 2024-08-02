#include "finish.hpp"

finishLine ::finishLine (int x, int y, int width, int height, SDL_Texture* tex)
{
    position.x = x;
    position.y = y;
    position.w = width;
    position.h = height;
    texture = tex;
}

void finishLine::render(SDL_Renderer* renderer, Vector2f cameraOffset) {
    SDL_Rect renderQuad = { position.x - cameraOffset.x, position.y - cameraOffset.y, position.w, position.h };
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
    
}

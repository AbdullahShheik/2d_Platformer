#include "RenderWindow.hpp"
using namespace std;

RenderWindow::RenderWindow(const char* title, int width, int height)
    : window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
    }
}

void RenderWindow::renderHealthBar(int health, Vector2f cameraOffset) {
    int barWidth = 200;
    int barHeight = 20;
    int borderThickness = 2;
    
    float healthPercentage = health / 100.0f; 
    int filledBarWidth = (int)(barWidth * healthPercentage);

    SDL_Rect borderRect = { 20, 20, barWidth, barHeight };
    SDL_Rect filledRect = { 20, 20, filledBarWidth, barHeight };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for health
    SDL_RenderFillRect(renderer, &filledRect);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for border
    SDL_RenderDrawRect(renderer, &borderRect);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
    if (texture == NULL)
    {
        cout << "IMG_LoadTexture Error: " << IMG_GetError() << endl;
    }
    return texture;
}

int RenderWindow::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity, Vector2f cameraOffSet)
{
    SDL_Rect src;
    src.h = entity.getCurrentFrame().h;
    src.w = entity.getCurrentFrame().w;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;

    SDL_Rect dest;
    dest.h = entity.getCurrentFrame().h * 2 ; 
    dest.w = entity.getCurrentFrame().w * 2; 
    dest.x = entity.getPos().x - cameraOffSet.x ;
    dest.y = entity.getPos().y - cameraOffSet.y ; 

    SDL_RenderCopy(renderer, entity.getTex(), &src, &dest);
}

void RenderWindow::renderPlatform(Entity& entity, Vector2f cameraOffSet)
{
    SDL_Rect src;
    src.h = entity.getCurrentFrame().h;
    src.w = entity.getCurrentFrame().w;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;

    SDL_Rect dest;
    dest.h = entity.getCurrentFrame().h ; 
    dest.w = entity.getCurrentFrame().w ; 
    dest.x = entity.getPos().x - cameraOffSet.x;
    dest.y = entity.getPos().y - cameraOffSet.y; 

    SDL_RenderCopy(renderer, entity.getTex(), &src, &dest);
}

void RenderWindow ::renderBackground(Entity& entity, Vector2f cameraOffSet)
{
    SDL_Rect src;
    src.h = entity.getCurrentFrame().h;
    src.w = entity.getCurrentFrame().w;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;

    SDL_Rect dest;
    dest.h = entity.getCurrentFrame().h; 
    dest.w = entity.getCurrentFrame().w; 
    dest.x = entity.getPos().x - cameraOffSet.x;
    dest.y = entity.getPos().y - cameraOffSet.y; 

    SDL_RenderCopy(renderer, entity.getTex(), &src, &dest);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUP()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
}

SDL_Renderer* RenderWindow::getRenderer() const {
    return renderer;
}

void RenderWindow::renderStartScreen(SDL_Texture* texture)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 1280;
    src.h = 720;

    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    dst.w = 1280;
    dst.h = 720;

    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::renderTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect) {
    SDL_RenderCopy(renderer, texture, srcRect, dstRect);
}

void RenderWindow::renderFinishLine(finishLine& finish, Vector2f cameraOffSet) {
    finish.render(renderer, cameraOffSet);
}

void RenderWindow::renderPowerLife(PowerLife& power, Vector2f cameraOffset) {
    power.renderPower(renderer, cameraOffset);
}
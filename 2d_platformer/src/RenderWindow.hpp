#pragma once
#ifndef RENDER_WINDOW_HPP
#define RENDER_WINDOW_HPP

#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"
#include "health.hpp"
#include "powerLife.hpp"
#include "SDL_mixer.h"
#include "finish.hpp"

#include <iostream>

class RenderWindow {
public:
    RenderWindow(const char* title, int width, int height);
    SDL_Texture* loadTexture(const char* filePath);

    int getRefreshRate();

    void clear();
    void render(Entity& entity, Vector2f cameraOffSet);
    void display();
    void cleanUP();
    void renderBackground(Entity& entity, Vector2f cameraOffSet);
    void renderPlatform(Entity& entity, Vector2f cameraOffSet);
    void renderHealthBar(int health, Vector2f cameraOffset);
    void renderTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect);
    void renderFinishLine(finishLine& finish, Vector2f cameraOffSet);
    void renderPowerLife(PowerLife& power, Vector2f cameraOffSet);


    SDL_Renderer* getRenderer() const;
    void renderStartScreen(SDL_Texture* texture);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif

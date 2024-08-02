#pragma once

#include "Entity.hpp"
#include "health.hpp"

class Player : public Entity {
public:
    Player(Vector2f pos, SDL_Texture* tex);
    void handleInput(const SDL_Event& event);
    void update(float deltaTime);
    int getHealth() const;
    void setHealth(int health); 
    void reduceHealth(float amount);

    void setColorMod(SDL_Texture* tex, int r, int g, int b);
    void resetColorMod(SDL_Texture* tex);

    void handleCollision();

    Vector2f getVelocity() const;
    void setVelocity(const Vector2f& velocity);
    void handlePlayerDeath();

    void setInCollision(bool inCollision);
    bool isInCollision() const;

    void increaseHealth(float amount );
private:
    Vector2f velocity;
    bool onGround;
    int jumpCount;
    void applyGravity(float deltaTime);
    void jump();
    bool inCollision;
    Health health;

    SDL_Texture* texture;
    SDL_Color originalColor;
};

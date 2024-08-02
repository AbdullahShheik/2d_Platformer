#pragma once

#include "Entity.hpp"
#include "math.hpp"

class Enemy : public Entity {
public:
    Enemy(Vector2f pos, SDL_Texture* tex);
    void update(float deltaTime);
    void setVelocity(const Vector2f& vel);
    void update2(float deltaTime);
    
    

private:
    Vector2f velocity;
    void applyGravity(float deltaTime);
    void move();
    void move2();
};

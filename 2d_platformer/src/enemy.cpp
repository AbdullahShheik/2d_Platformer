#include "enemy.hpp"

Enemy::Enemy(Vector2f pos, SDL_Texture* tex)
    : Entity(pos, tex), velocity(Vector2f(0, 0)) {
    setSourceRect(0, 0, 100, 100);
}

void Enemy::update(float deltaTime) {
    applyGravity(deltaTime);
    move();

    getPos().x += velocity.x * deltaTime;
    getPos().y += velocity.y * deltaTime;

    if (getPos().y >= 500.0f) { 
        getPos().y = 500.0f;
        velocity.y = 0;
    }
}

void Enemy::update2(float deltaTime) {
    applyGravity(deltaTime);
    move2();

    getPos().x += velocity.x * deltaTime;
    getPos().y += velocity.y * deltaTime;

    if (getPos().y >= 500.0f) { 
        getPos().y = 500.0f;
        velocity.y = 0;
    }
}

void Enemy::applyGravity(float deltaTime) {
    velocity.y += 981.0f * deltaTime; // Gravity strength
}

void Enemy::move() {
    //  Move back and forth
    if (getPos().x <= 500) {
        velocity.x = 100.0f; // Move right
    } else if (getPos().x >= 1100) { 
        velocity.x = -100.0f; // Move left
    }
}

void Enemy::move2() {
    //  Move back and forth
    if (getPos().x <= 1500) {
        velocity.x = 100.0f; // Move right
    } else if (getPos().x >= 2100) { 
        velocity.x = -100.0f; // Move left
    }
}

void Enemy::setVelocity(const Vector2f& vel) {
    velocity = vel;
}

#include "player.hpp"
#include "health.hpp"

Player::Player(Vector2f pos, SDL_Texture* tex)
    : Entity(pos, tex), velocity(Vector2f(0, 0)), onGround(false), jumpCount(0), health(100, 100) {
    setSourceRect(0, 0, 64, 64);
    Uint8 r, g, b;
    SDL_GetTextureColorMod(tex, &r, &g, &b);
    originalColor = {r, g, b, 255};
}

void Player::handleInput(const SDL_Event& event) {
    if (inCollision) return;

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_LEFT]) {
        velocity.x = -200.0f; // Move left
    } else if (state[SDL_SCANCODE_RIGHT]) {
        velocity.x = 200.0f; // Move right
    } else {
        velocity.x = 0.0f; // No horizontal movement
    }

    if (state[SDL_SCANCODE_SPACE]) {
        jump();
    }
}

void Player::update(float deltaTime) {
    applyGravity(deltaTime);

    getPos().x += velocity.x * deltaTime;
    getPos().y += velocity.y * deltaTime;

    if (getPos().y >= 600.0f) { // Assuming ground is at y = 600
        getPos().y = 600.0f; // Reset position to ground level
        velocity.y = 0; // Stop falling
        onGround = true;
        jumpCount = 0; // Reset jump count when landing
    } else {
        onGround = false;
    }
}

void Player::applyGravity(float deltaTime) {
    velocity.y += 981.0f * deltaTime; // Gravity strength
}

void Player::jump() {
    if (onGround || jumpCount <= 2) {
        velocity.y = -600.0f; // Jump strength
        onGround = false;
        jumpCount++;
    }
}

int Player::getHealth() const {
    return health.getHealth();
}

void Player::reduceHealth(float amount) {
    health.takeDamage(amount);
}

void Player::setColorMod(SDL_Texture* tex, int r, int g, int b) {
    SDL_SetTextureColorMod(tex, r, g, b);
}

void Player::resetColorMod(SDL_Texture* tex) {
    SDL_SetTextureColorMod(tex, originalColor.r, originalColor.g, originalColor.b);
}

void Player::handleCollision() {
    if (velocity.x > 0) {
        velocity.x = -200.0f;
        velocity.y = -500.0f;
    } else if (velocity.x < 0) {
        velocity.x = 200.0f;
        velocity.y = -500.0f;
    }
}

Vector2f Player::getVelocity() const {
    return velocity;
}

void Player::setVelocity(const Vector2f& vel) {
    velocity = vel;
}

void Player::handlePlayerDeath() {
    cout << "Game Over" << endl;
}

void Player::setInCollision(bool inCollision) {
    this->inCollision = inCollision;
}

bool Player::isInCollision() const {
    return inCollision;
}

void Player::setHealth(int health) {
    this->health.setHealth(health);
}

void Player::increaseHealth(float amount)
{
    health.takeHealth(amount);
}

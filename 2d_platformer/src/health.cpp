#include "health.hpp"

Health::Health(int maxHealth, int currentHealth) : maxHealth(maxHealth), currentHealth(currentHealth) {}

void Health::takeDamage(float damage) {
    if (damage >= currentHealth) {
        currentHealth = 0; 
    } else {
        currentHealth -= damage;
    }
}

void Health::takeHealth(float amount)
{
    if ((amount+currentHealth)>100)
    {
        currentHealth = 100;
    }
    else
    {
        currentHealth+=amount;
    }
}

void Health::heal(int amount) {
    currentHealth += amount;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

int Health::getHealth() const {
    return currentHealth;
}

int Health::getMaxHealth() const {
    return maxHealth;
}

void Health::setHealth(int health) {
    currentHealth = health;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

#pragma once


class Health {
    public:
        Health(int maxHealth, int currentHealth);
        void takeDamage(float amount);
        void takeHealth(float amount);
        void heal(int amount);
        int getHealth() const;
        int getMaxHealth() const;
        void setHealth(int health);

    private:
        int maxHealth;
        int currentHealth;
};
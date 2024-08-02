#pragma once

#include "Entity.hpp"

class Platform : public Entity {
public:
    Platform(Vector2f pos, SDL_Texture* tex);
};
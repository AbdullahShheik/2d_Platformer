#pragma once

#include "math.hpp"
class Camera
{
    public:
        Camera(Vector2f pos, int screenWidth, int screenHeight, int w_width, int w_height);
        void update(Vector2f playerPos);
        Vector2f getCameraOffset() const;
        void setPos(const Vector2f& p_pos);
    private:
        Vector2f pos;
        int screenWidth;
        int screenHeight;
        int w_width;
        int w_height;
};
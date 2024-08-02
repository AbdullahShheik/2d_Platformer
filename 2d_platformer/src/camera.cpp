#include "camera.hpp"

Camera::Camera(Vector2f pos, int screenWidth, int screenHeight, int w_width, int w_height) : pos(pos), screenWidth(screenWidth), screenHeight(screenHeight), w_width(w_width), w_height(w_height) {}

void Camera::update(Vector2f playerPos) {
    pos.x = playerPos.x - screenWidth / 2;
    if (pos.x < 0) {
        pos.x = 0;}
    if (pos.x > w_width - screenWidth)
    { pos.x = w_width - screenWidth ;}
    if (pos.y > w_height - screenHeight)
    { pos.y = w_height - screenHeight ;}
        
}

Vector2f Camera::getCameraOffset() const {
    return pos;
}

void Camera::setPos(const Vector2f& p_pos) {
    pos = p_pos;
}
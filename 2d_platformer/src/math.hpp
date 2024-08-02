#pragma once
#include <iostream>
using namespace std;


class Vector2f{
    public:
        float x,y;
        Vector2f():x(0.0f), y(0.0f) {}
        Vector2f(float x,float y): x(x), y(y) {}
        
};
#pragma once

#include <math.h>

struct Vector2
{
    float x;
    float y;
    float magnitude() {
        return sqrtf(x * x + y * y);
    }
    float magnitude_sq() {
        return x * x + y * y;
    }
};

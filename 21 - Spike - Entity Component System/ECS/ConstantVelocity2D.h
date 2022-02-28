#pragma once

#include "BaseComponent.h"
#include "Vector2.h"

// holding the constant velocity that affects the body velocity
struct ConstantVelocity2D : public BaseComponent {
	ConstantVelocity2D();
	Vector2 velocity;
};
#pragma once

#include "BaseComponent.h"
#include "Vector2.h"
// allow the entity to be affected by physics
struct RigidBody2D : public BaseComponent {
	RigidBody2D();
	Vector2 velocity;
	float gravityScale = 1.0;
};
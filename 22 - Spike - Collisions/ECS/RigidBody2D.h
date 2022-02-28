#pragma once

#include "BaseComponent.h"
#include "Vector2.h"

// allow the entity to be affected by physics
struct RigidBody2D : public BaseComponent {
	Vector2 velocity = Vector2{ 0,0 };
	float gravityScale = 1.0;
	float mass = 1.0;

	void AddForce(Vector2 f) {
		velocity.x += f.x;
		velocity.y += f.y;
	}
};
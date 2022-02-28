#pragma once

#include "BaseComponent.h"

// allow the entity to be affected by physics
struct RigidBody2D : public BaseComponent {
	RigidBody2D() : BaseComponent() {}
	RigidBody2D(const RigidBody2D& obj) : BaseComponent(obj) {
		velocity = obj.velocity;
		gravityScale = obj.gravityScale;
		mass = obj.mass;
	};
	RigidBody2D(json obj) : BaseComponent(obj) {
		velocity.x = obj["velocity"]["x"].is_null() ? velocity.x : obj["velocity"]["x"];
		velocity.y = obj["velocity"]["y"].is_null() ? velocity.y : obj["velocity"]["y"];
		gravityScale = obj["gravityScale"].is_null() ? gravityScale : obj["gravityScale"];
		mass = obj["mass"].is_null() ? mass : obj["mass"];
	} // json constructor
	~RigidBody2D() {}
	BaseComponent* Clone() {
		return new RigidBody2D(*this);
	};
	Vector2 velocity = Vector2{ 0,0 };
	float gravityScale = 1.0;
	float mass = 1.0;

	void AddForce(Vector2 f) {
		velocity.x += f.x;
		velocity.y += f.y;
	}
};
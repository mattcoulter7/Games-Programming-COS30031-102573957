#pragma once

#include "BaseComponent.h"

struct Collider2D : public BaseComponent {
	Collider2D(size_t entityid) : BaseComponent(entityid) {};
	Vector2 position = Vector2{ 0,0 }; // gets updated to the transform position + offset
	Vector2 offset = Vector2{ 0,0 };
	
	virtual Vector2 GetCenter() = 0;
	virtual Vector2 GetFarthestPoint(Vector2 direction) = 0;
};
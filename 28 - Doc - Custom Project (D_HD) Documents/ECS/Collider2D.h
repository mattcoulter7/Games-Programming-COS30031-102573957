#pragma once

#include "BaseComponent.h"

struct Collider2D : public BaseComponent {
	Collider2D() : BaseComponent() {};
	Collider2D(const Collider2D& obj) : BaseComponent(obj) {
		position = obj.position;
		offset = obj.offset;
	};
	Collider2D(json obj) : BaseComponent(obj) {
		offset.x = obj["offset"]["x"].is_null() ? offset.x : obj["offset"]["x"];
		offset.y = obj["offset"]["y"].is_null() ? offset.y : obj["offset"]["y"];

		// system will update the position
	}
	~Collider2D() {}
	Vector2 position = Vector2{ 0,0 }; // gets updated to the transform position + offset
	Vector2 offset = Vector2{ 0,0 };
	
	virtual Vector2 GetCenter() = 0;
	virtual Vector2 GetFarthestPoint(Vector2 direction) = 0;
};
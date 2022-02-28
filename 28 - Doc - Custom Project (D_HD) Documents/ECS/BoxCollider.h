#pragma once

#include <array>

#include "Collider2D.h"
#include "LineCollider.h"

struct BoxCollider : public Collider2D {
	BoxCollider() : Collider2D() {}
	BoxCollider(const BoxCollider& obj) : Collider2D(obj) {
		// don't copy lines as the system will handle that creation
		width = obj.width;
		height = obj.height;
	};
	BoxCollider(json obj) : Collider2D(obj) {
		width = obj["width"].is_null() ? width : obj["width"];
		height = obj["height"].is_null() ? height : obj["height"];
	}
	~BoxCollider() {}
	BaseComponent* Clone() {
		return new BoxCollider(*this);
	};
	std::array<LineCollider*,4> lines = std::array<LineCollider*, 4>();

	Vector2 GetCenter() {
		return Vector2{}; // collision is based off the lines, so keep null
	};
	Vector2 GetFarthestPoint(Vector2 direction) {
		return Vector2{}; // collision is based off the lines, so keep null
	};

	float width = 0;
	float height = 0;
};
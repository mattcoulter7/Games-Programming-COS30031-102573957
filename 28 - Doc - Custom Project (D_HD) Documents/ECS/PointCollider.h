#pragma once

#include <array>

#include "Collider2D.h"

struct PointCollider : public Collider2D {
	PointCollider() : Collider2D() {}
	PointCollider(const PointCollider& obj) : Collider2D(obj) {};
	PointCollider(json obj) : Collider2D(obj) {}
	~PointCollider() {}
	BaseComponent* Clone() {
		return new PointCollider(*this);
	};
	Vector2 GetCenter() {
		return position;
	}
	Vector2 GetFarthestPoint(Vector2 direction) {
		return position;
	};
};
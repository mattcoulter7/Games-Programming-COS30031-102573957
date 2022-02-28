#pragma once

#include "Collider2D.h"

struct CircleCollider : public Collider2D {
	CircleCollider() : Collider2D() {}
	CircleCollider(const CircleCollider& obj) : Collider2D(obj) {
		radius = obj.radius;
	};
	CircleCollider(json obj) : Collider2D(obj) {
		radius = obj["radius"].is_null() ? radius : obj["radius"];
	}
	~CircleCollider() {}
	BaseComponent* Clone() {
		return new CircleCollider(*this);
	};
	float radius = 1.0;

	Vector2 GetCenter() override {
		return position;
	}

	Vector2 GetFarthestPoint(Vector2 dir) override {
		Vector2 pos = position; // position in world space
		return pos + (dir.GetNormalised() * radius);
	}
};
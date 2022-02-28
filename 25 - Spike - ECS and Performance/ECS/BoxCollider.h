#pragma once

#include <array>

#include "Collider2D.h"
#include "LineCollider.h"

struct BoxCollider : public Collider2D {
	BoxCollider(size_t entityid) : Collider2D(entityid) {}
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
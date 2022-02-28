#pragma once

#include "Collider2D.h"

struct CircleCollider : public Collider2D {
	CircleCollider(size_t entityid) : Collider2D(entityid) {}
	float radius = 1.0;

	Vector2 GetCenter() override;
	Vector2 GetFarthestPoint(Vector2 direction) override;
};
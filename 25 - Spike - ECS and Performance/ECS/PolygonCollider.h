#pragma once

#include "Collider2D.h"

struct PolygonCollider : public Collider2D {
	PolygonCollider(size_t entityid) : Collider2D(entityid) {};
	std::vector<Vector2> localPts; // relative to center
	std::vector<Vector2> worldPts; // actual position
	std::vector<Vector2> edges; // vectors of each edge (between points)

	Vector2 GetCenter() override;
	Vector2 GetFarthestPoint(Vector2 direction) override;
};
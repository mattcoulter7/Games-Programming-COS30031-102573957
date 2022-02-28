#pragma once

#include "PolygonCollider.h"

struct RectangleCollider : public PolygonCollider {
	RectangleCollider(size_t entityid) : PolygonCollider(entityid) {
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
	}
	float width = 0;
	float height = 0;
};
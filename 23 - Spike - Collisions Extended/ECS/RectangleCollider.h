#pragma once

#include "PolygonCollider.h"

struct RectangleCollider : public PolygonCollider {
	RectangleCollider() : PolygonCollider() {
		localPts[0] = Vector2{ 0,0 }; 
		localPts[1] = Vector2{ 0,0 };
		localPts[2] = Vector2{ 0,0 };
		localPts[3] = Vector2{ 0,0 };
	}
	float width = 0;
	float height = 0;
};
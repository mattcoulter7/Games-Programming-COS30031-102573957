#pragma once

#include "PolygonCollider.h"

struct LineCollider : public PolygonCollider {
	LineCollider(size_t entityid) : PolygonCollider(entityid) {
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
	}
	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
};
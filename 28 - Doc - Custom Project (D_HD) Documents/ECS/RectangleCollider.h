#pragma once

#include "PolygonCollider.h"

struct RectangleCollider : public PolygonCollider {
	RectangleCollider() : PolygonCollider() {
		InitPts();
	}
	RectangleCollider(const RectangleCollider& obj) : PolygonCollider(obj) {
		width = obj.width;
		height = obj.height;
		//InitPts(); // don't init cause the polygon collider copies them already
	};
	RectangleCollider(json obj) : PolygonCollider(obj) {
		width = obj["width"].is_null() ? width : obj["width"];
		height = obj["height"].is_null() ? height : obj["height"];
		InitPts();
	}
	~RectangleCollider() {}
	BaseComponent* Clone() {
		return new RectangleCollider(*this);
	};
	void InitPts() {
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
	}
	float width = 0;
	float height = 0;
};
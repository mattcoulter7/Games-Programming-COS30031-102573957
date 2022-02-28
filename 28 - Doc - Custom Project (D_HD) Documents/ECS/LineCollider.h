#pragma once

#include "PolygonCollider.h"

struct LineCollider : public PolygonCollider {
	LineCollider() : PolygonCollider() {
		InitPts();
	}
	LineCollider(const LineCollider& obj) : PolygonCollider(obj) {
		x1 = obj.x1;
		y1 = obj.y1;
		x2 = obj.x2;
		y2 = obj.y2;
		// InitPts(); don't init as polygon collider handles it
	};
	LineCollider(json obj) : PolygonCollider(obj) {
		x1 = obj["x1"].is_null() ? x1 : obj["x1"];
		y1 = obj["y1"].is_null() ? y1 : obj["y1"];
		x2 = obj["x2"].is_null() ? x2 : obj["x2"];
		y2 = obj["y2"].is_null() ? y2 : obj["y2"];
		InitPts();
	}
	~LineCollider() {}
	BaseComponent* Clone() {
		return new LineCollider(*this);
	};
	void InitPts() {
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
	}
	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
};
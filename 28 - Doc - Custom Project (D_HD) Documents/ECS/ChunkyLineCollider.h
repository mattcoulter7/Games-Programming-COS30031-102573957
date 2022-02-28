
#pragma once

#include "PolygonCollider.h"

/*
	Line Collider but with a width
*/

struct ChunkyLineCollider : public PolygonCollider {
	ChunkyLineCollider() : PolygonCollider() {
		InitPts();
	}
	ChunkyLineCollider(const ChunkyLineCollider& obj) : PolygonCollider(obj) {
		width = obj.width;
		x1 = obj.x1;
		y1 = obj.y1;
		x2 = obj.x2;
		y2 = obj.y2;
		//InitPts(); // don't init cause the polygon collider copies them already
	};
	ChunkyLineCollider(json obj) : PolygonCollider(obj) {
		width = obj["width"].is_null() ? width : obj["width"];
		x1 = obj["x1"].is_null() ? x1 : obj["x1"];
		y1 = obj["y1"].is_null() ? y1 : obj["y1"];
		x2 = obj["x2"].is_null() ? x2 : obj["x2"];
		y2 = obj["y2"].is_null() ? y2 : obj["y2"];
		InitPts();
	}
	~ChunkyLineCollider() {}
	BaseComponent* Clone() {
		return new ChunkyLineCollider(*this);
	};
	void InitPts() {
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
		localPts.push_back(Vector2{ 0,0 });
	}
	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
	float width = 0;
};
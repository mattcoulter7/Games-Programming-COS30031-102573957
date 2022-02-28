#pragma once

#include "Collider2D.h"

class RectangleCollider;
class LineCollider;
class PolygonCollider;
class BoxCollider;
class ChunkyLineCollider;

class Collider2DTransformer {
public:
	// set world position of collider based on transform
	void SetWorldPosition(Collider2D* col);
	// transform relative points to world points based on transform
	void SetRectanglePoints(RectangleCollider* col);
	void SetLinePoints(LineCollider* col);
	void SetChunkyLinePoints(ChunkyLineCollider* col);
	// transform relative points to world points based on transform
	void SetWorldPoints(PolygonCollider* col);
	void SetBoxLines(BoxCollider* col);
	// the the edge vectors that join each of the worl points
	void SetEdges(PolygonCollider* col);
};
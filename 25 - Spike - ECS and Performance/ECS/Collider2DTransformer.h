
#include "RectangleCollider.h"
#include "BoxCollider.h"

#include "ECS.h"
#include "Transform2D.h"

class Collider2DTransformer {
public:
	// set world position of collider based on transform
	void SetWorldPosition(Collider2D* col);
	// transform relative points to world points based on transform
	void SetRectanglePoints(RectangleCollider* col);
	void SetLinePoints(LineCollider* col);
	// transform relative points to world points based on transform
	void SetWorldPoints(PolygonCollider* col);
	void SetBoxLines(BoxCollider* col);
	// the the edge vectors that join each of the worl points
	void SetEdges(PolygonCollider* col);
};
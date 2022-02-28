#include "CircleCollider.h"

#include "ECS.h"
Vector2 CircleCollider::GetCenter() {
	return position;
}

Vector2 CircleCollider::GetFarthestPoint(Vector2 dir) {
	Vector2 pos = position; // position in world space
	return pos + (dir.GetNormalised() * radius);
}
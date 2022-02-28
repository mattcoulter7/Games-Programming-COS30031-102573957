#pragma once

#include "BaseComponent.h"

// holds positional information of the entity
struct Transform2D : public BaseComponent{
	Transform2D(size_t entityid) : BaseComponent(entityid) {}
	Vector2 position = Vector2{ 0,0 };
	double rotation = 0; // rotation in radians
	Vector2 scale = Vector2{ 1,1 };

	// local space to world space
	Vector2 TransformPoint(Vector2 pt) {
		// apply rotations
		pt.RotateRadians(rotation);

		// apply scale
		pt.x *= scale.x;
		pt.y *= scale.y;

		// apply the transformation
		pt += position;
		return pt;
	}

	//world space to local space
	Vector2 InverseTransformPoint(Vector2 pt) {
		// remove the transformation
		pt -= position;

		// remove scale
		pt.x /= scale.x;
		pt.y /= scale.y;

		// remove rotation
		pt.RotateRadians(-rotation);

		return pt;
	}
};
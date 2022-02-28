#pragma once

#include "BaseComponent.h"

// holds positional information of the entity
struct Transform2D : public BaseComponent{
	Transform2D() : BaseComponent() {}
	Transform2D(const Transform2D& obj) : BaseComponent(obj){
		position = obj.position;
		rotation = obj.rotation;
		scale = obj.scale;
	};  // copy constructor
	Transform2D(json obj) : BaseComponent(obj) {
		position.x = obj["position"]["x"].is_null() ? position.x : obj["position"]["x"];
		position.y = obj["position"]["y"].is_null() ? position.y : obj["position"]["y"];

		rotation = obj["rotation"].is_null() ? rotation : obj["rotation"];

		scale.x = obj["scale"]["x"].is_null() ? scale.x : obj["scale"]["x"];
		scale.y = obj["scale"]["y"].is_null() ? scale.y : obj["scale"]["y"];
	} // json constructor
	~Transform2D() {};// destructor
	BaseComponent* Clone() {
		return new Transform2D(*this);
	};

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
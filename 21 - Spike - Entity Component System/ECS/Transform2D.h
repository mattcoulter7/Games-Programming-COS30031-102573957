#pragma once

#include "BaseComponent.h"
#include "Vector2.h"

// holds positional information of the entity
struct Transform2D : public BaseComponent{
	Transform2D();
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;
};
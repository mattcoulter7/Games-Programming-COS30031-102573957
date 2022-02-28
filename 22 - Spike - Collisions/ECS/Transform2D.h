#pragma once

#include "BaseComponent.h"
#include "Vector2.h"

// holds positional information of the entity
struct Transform2D : public BaseComponent{
	Vector2 position = Vector2{ 0,0 };
	Vector2 rotation = Vector2{ 0,0 };
	Vector2 scale = Vector2{ 1,1 };
};
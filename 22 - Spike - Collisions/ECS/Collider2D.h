#pragma once

#include "BaseComponent.h"
#include "Vector2.h"

struct Collider2D : public BaseComponent {
	Vector2 position = Vector2{ 0,0 };
	Vector2 offset = Vector2{ 0,0 };
};
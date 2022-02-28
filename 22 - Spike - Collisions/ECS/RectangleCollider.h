#pragma once

#include "Collider2D.h"
#include "Vector2.h"

struct RectangleCollider : public Collider2D {
	float width = 0;
	float height = 0;
};
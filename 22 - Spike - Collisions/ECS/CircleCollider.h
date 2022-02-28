#pragma once

#include "Collider2D.h"
#include "Vector2.h"

struct CircleCollider : public Collider2D {
	float radius = 1.0;
};
#pragma once

#include "ConstantVelocity2D.h"

ConstantVelocity2D::ConstantVelocity2D() : BaseComponent() {
	velocity = Vector2{ 0,0 };
}
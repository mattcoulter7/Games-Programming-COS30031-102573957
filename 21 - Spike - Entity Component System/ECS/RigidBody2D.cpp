#pragma once

#include "RigidBody2D.h"

RigidBody2D::RigidBody2D() : BaseComponent() {
	velocity = Vector2{ 0,0 };
}
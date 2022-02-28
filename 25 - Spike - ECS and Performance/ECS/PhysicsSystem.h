#pragma once

#include "ECS.h"

#include "Transform2D.h"
#include "RigidBody2D.h"

class PhysicsSystem : public System {
public:
	PhysicsSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
};
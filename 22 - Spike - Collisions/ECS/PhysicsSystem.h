#pragma once

#include "System.h"

class PhysicsSystem : public System {
public:
	PhysicsSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
};
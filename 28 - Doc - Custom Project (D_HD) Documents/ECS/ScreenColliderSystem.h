#pragma once

#include "System.h"

#include "ScreenCollider.h"

class ScreenColliderSystem : public System {
public:
	ScreenColliderSystem();
	ScreenColliderSystem(json obj);
	~ScreenColliderSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
private:
	void AddEventListeners() override;
	bool HandleScreenCollision(ScreenCollider* col);
};
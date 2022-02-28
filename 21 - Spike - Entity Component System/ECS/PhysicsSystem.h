#pragma once

#include "System.h"

class PhysicsSystem : public System {
public:
	PhysicsSystem();
	void Update(ComponentManager* cm) override;
	void Render(ComponentManager* cm) override;
};
#pragma once

#include "PhysicsSystem.h"

#include "Transform2D.h"
#include "ConstantVelocity2D.h"

PhysicsSystem::PhysicsSystem() : System() {

}
void PhysicsSystem::Update(ComponentManager* cm) {
	std::vector<Transform2D*> transforms = cm->GetComponents<Transform2D>();

	for (Transform2D* tf : transforms) {
		// update transform from constant velocities
		std::vector<ConstantVelocity2D*> cvs = cm->GetComponents<ConstantVelocity2D>(tf->entityid);

		for (ConstantVelocity2D* cv : cvs) {
			tf->position.x += cv->velocity.x;
			tf->position.y += cv->velocity.y;
		}
	}

}
void PhysicsSystem::Render(ComponentManager* cm) {

}
#pragma once

#include "PhysicsSystem.h"

const float GRAVITY = 9.8;

PhysicsSystem::PhysicsSystem() : System() {}

void PhysicsSystem::Update(double dt) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	// update transform from constant velocities
	std::vector<RigidBody2D*> rbs = cm->GetComponents<RigidBody2D>();

	for (RigidBody2D* rb : rbs) {
		// add the gravity
		rb->AddForce(Vector2{ 0, GRAVITY * rb->gravityScale * rb->mass });

		// update the position
		Transform2D* tf = cm->GetComponent<Transform2D>(rb->entityid);
		tf->position += rb->velocity * dt;
	}
}
void PhysicsSystem::Render(SDL_Renderer* renderer) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
}
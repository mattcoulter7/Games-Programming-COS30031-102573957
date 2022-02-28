#pragma once

#include "PhysicsSystem.h"

#include "ECS.h"
#include "Debug.h"
#include "RigidBody2D.h"
#include "Transform2D.h"

const float GRAVITY = 9.8;

PhysicsSystem::PhysicsSystem() : System() {
	AddEventListeners();
}
PhysicsSystem::PhysicsSystem(json obj) : System(obj) {
	AddEventListeners();
}
PhysicsSystem::~PhysicsSystem() {

};
void PhysicsSystem::AddEventListeners() {}

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
	if (ECS::ECS_ENGINE()->debug) {
		ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
		for (auto tf : cm->GetComponents<Transform2D>()) {
			Debug::Instance()->RenderPoint(renderer, tf->position.x, tf->position.y);
		}
	}
}
#pragma once

#include "ScreenColliderSystem.h"

#include "ECS.h"

#include "Render2DSystem.h"

#include "Transform2D.h"
#include "RigidBody2D.h"

ScreenColliderSystem::ScreenColliderSystem() : System() {
	AddEventListeners();
}

ScreenColliderSystem::ScreenColliderSystem(json obj) : System(obj) {
	AddEventListeners();

}
ScreenColliderSystem::~ScreenColliderSystem(){}
void ScreenColliderSystem::AddEventListeners() {}


void ScreenColliderSystem::Update(double dt) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	// ---------- SCREEN COLLIDERS  ---------- //
	std::vector<ScreenCollider*> scs = cm->GetComponents<ScreenCollider>(); // screen colliders
	for (ScreenCollider* col : scs) {
		HandleScreenCollision(col);
	}
}
void ScreenColliderSystem::Render(SDL_Renderer* renderer) {

}


bool ScreenColliderSystem::HandleScreenCollision(ScreenCollider* col) {
	SystemManager* sm = ECS::ECS_ENGINE()->GetSystemManager();
	Render2DSystem* rs = sm->GetSystem<Render2DSystem>(); // get width and height
	if (rs == nullptr) return false;
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();

	// transform position to calculate collision
	Transform2D* tf = cm->GetComponent<Transform2D>(col->entityid);
	if (tf == nullptr) return false;

	// rigid body to update velocity
	RigidBody2D* rb = cm->GetComponent<RigidBody2D>(col->entityid);
	if (rb == nullptr) return false;

	// bounce with edge of screen
	if (tf->position.x >= rs->width || tf->position.x <= 0) {
		rb->velocity.x = -rb->velocity.x;
	}
	if (tf->position.y >= rs->height || tf->position.y <= 0) {
		rb->velocity.y = -rb->velocity.y;
	}
	return true;
};
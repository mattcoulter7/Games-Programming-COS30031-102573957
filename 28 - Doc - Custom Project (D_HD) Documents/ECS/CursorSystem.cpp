#pragma once

#include "CursorSystem.h"

#include "ECS.h"

#include "Collider2DSystem.h"

#include "Cursor.h"
#include "Collider2D.h"
#include "Transform2D.h"
#include "PointCollider.h"

CursorSystem::CursorSystem() : System() {
	AddEventListeners();
}

CursorSystem::CursorSystem(json obj) : System(obj) {
	AddEventListeners();
}
CursorSystem::~CursorSystem() {

};
void CursorSystem::AddEventListeners() {
	EventDispatcher::AddEventListener("CollisionIn", &CursorSystem::DispatchMouseInEvent, this);
	EventDispatcher::AddEventListener("CollisionEnter", &CursorSystem::DispatchMouseEnterEvent, this);
	EventDispatcher::AddEventListener("CollisionOut", &CursorSystem::DispatchMouseOutEvent, this);
	EventDispatcher::AddEventListener("CollisionExit", &CursorSystem::DispatchMouseExitEvent, this);

	EventDispatcher::AddEventListener("MouseMove", &CursorSystem::DispatchMouseMoveEvent, this);

	EventDispatcher::AddEventListener("Input", &CursorSystem::DispatchInputEvents, this);
	EventDispatcher::AddEventListener("InputDown", &CursorSystem::DispatchInputDownEvents, this);
	EventDispatcher::AddEventListener("InputUp", &CursorSystem::DispatchInputUpEvents, this);
}

void CursorSystem::Update(double dt) {
	if (cursorEntityId == -1) {
		ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
		Cursor* cursor = cm->GetComponent<Cursor>();
		if (cursor != nullptr) {
			cursorEntityId = cursor->entityid;
		}
	}
}

void CursorSystem::Render(SDL_Renderer* renderer) {
}

bool CursorSystem::MouseIn(size_t colId) {
	// return true if the mouse is inside of a collider
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	SystemManager* sm = ECS::ECS_ENGINE()->GetSystemManager();
	Collider2DSystem* colliderSystem = sm->GetSystem<Collider2DSystem>();
	PointCollider* cursorCollider = cm->GetComponent<PointCollider>(cursorEntityId);
	if (cursorCollider == nullptr || colliderSystem == nullptr) return false;

	return colliderSystem->collisionManager.GetCollision(cursorCollider->id, colId);
}

bool CursorSystem::MouseEnter(size_t colId) {
	// return true when the mouse first enters a collider
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	SystemManager* sm = ECS::ECS_ENGINE()->GetSystemManager();
	Collider2DSystem* colliderSystem = sm->GetSystem<Collider2DSystem>();
	PointCollider* cursorCollider = cm->GetComponent<PointCollider>(cursorEntityId);
	if (cursorCollider == nullptr || colliderSystem == nullptr) return false;

	return colliderSystem->collisionManager.GetCollisionIn(cursorCollider->id, colId);
}

bool CursorSystem::MouseExit(size_t colId) {
	// return true when the mouse first exits a collider
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	SystemManager* sm = ECS::ECS_ENGINE()->GetSystemManager();
	Collider2DSystem* colliderSystem = sm->GetSystem<Collider2DSystem>();
	PointCollider* cursorCollider = cm->GetComponent<PointCollider>(cursorEntityId);
	if (cursorCollider == nullptr || colliderSystem == nullptr) return false;

	return colliderSystem->collisionManager.GetCollisionOut(cursorCollider->id, colId);
}

void CursorSystem::DispatchMouseMoveEvent(Vector2 pos, Vector2 vel) {
	// set the cursor position
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	Transform2D* tf = cm->GetComponent<Transform2D>(cursorEntityId);
	if (tf != nullptr) {
		Vector2 mousePos = Input::Instance()->GetMousePos();
		if (mousePos != tf->position) {
			// the mouse has moved
			Vector2 moveVelocity = tf->position.To(mousePos);
			tf->position = mousePos;
			DispatchMouseMoveEvent(tf->position, moveVelocity);
		}
	}

	// dispatch mouse move events on colliders
	SystemManager* sm = ECS::ECS_ENGINE()->GetSystemManager();
	Collider2DSystem* colliderSystem = sm->GetSystem<Collider2DSystem>();
	PointCollider* cursorCollider = cm->GetComponent<PointCollider>(cursorEntityId);
	if (cursorCollider == nullptr || colliderSystem == nullptr) return;

	std::vector<Collider2D*> colliders = colliderSystem->collisionManager.GetCollisions(cursorCollider->id);
	for (Collider2D* col : colliders) {
		EventDispatcher::Dispatch("ColliderMouseMove", pos, vel, col);
	}

}

void CursorSystem::DispatchMouseEnterEvent(Collider2D* col1,Collider2D* col2) {
	if (col1->entityid == cursorEntityId) {
		EventDispatcher::Dispatch("ColliderMouseEnter", col2);
	}
};
void CursorSystem::DispatchMouseExitEvent(Collider2D* col1, Collider2D* col2) {
	if (col1->entityid == cursorEntityId) {
		EventDispatcher::Dispatch("ColliderMouseExit", col2);
	}
};
void CursorSystem::DispatchMouseInEvent(Collider2D* col1, Collider2D* col2) {
	if (col1->entityid == cursorEntityId) {
		EventDispatcher::Dispatch("ColliderMouseIn", col2);
	}
};
void CursorSystem::DispatchMouseOutEvent(Collider2D* col1, Collider2D* col2) {
	if (col1->entityid == cursorEntityId) {
		EventDispatcher::Dispatch("ColliderMouseOut", col2);
	}
};

void CursorSystem::DispatchInputDownEvents(Uint8 input) {
	// down input when mouse is in a collider
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	SystemManager* sm = ECS::ECS_ENGINE()->GetSystemManager();
	Collider2DSystem* colliderSystem = sm->GetSystem<Collider2DSystem>();
	PointCollider* cursorCollider = cm->GetComponent<PointCollider>(cursorEntityId);
	if (cursorCollider == nullptr || colliderSystem == nullptr) return;

	std::vector<Collider2D*> colliders = colliderSystem->collisionManager.GetCollisions(cursorCollider->id);
	for (Collider2D* col : colliders) {
		EventDispatcher::Dispatch("ColliderInputDown", input, col);
	}
};
void CursorSystem::DispatchInputUpEvents(Uint8 input) {
	// up input when mouse is in a collider
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	SystemManager* sm = ECS::ECS_ENGINE()->GetSystemManager();
	Collider2DSystem* colliderSystem = sm->GetSystem<Collider2DSystem>();
	PointCollider* cursorCollider = cm->GetComponent<PointCollider>(cursorEntityId);
	if (cursorCollider == nullptr || colliderSystem == nullptr) return;

	std::vector<Collider2D*> colliders = colliderSystem->collisionManager.GetCollisions(cursorCollider->id);
	for (Collider2D* col : colliders) {
		EventDispatcher::Dispatch("ColliderInputUp", input, col);
	}
};
void CursorSystem::DispatchInputEvents(Uint8 input,bool down) {
	// input held down or up when mouse is in a collider
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	SystemManager* sm = ECS::ECS_ENGINE()->GetSystemManager();
	Collider2DSystem* colliderSystem = sm->GetSystem<Collider2DSystem>();
	PointCollider* cursorCollider = cm->GetComponent<PointCollider>(cursorEntityId);
	if (cursorCollider == nullptr || colliderSystem == nullptr) return;

	std::vector<Collider2D*> colliders = colliderSystem->collisionManager.GetCollisions(cursorCollider->id);
	for (Collider2D* col : colliders) {
		EventDispatcher::Dispatch("ColliderInput", input, down, col);
	}
};
#include "CollisionManager.h"

#include "EventDispatcher.hpp"

void CollisionManager::Update() {
	// clear all collision data
	for (auto& pair : collisions) {
		pair.second.clear();
	}

	// don't clear the state data as they constantly get set to in/out etc.
}
bool CollisionManager::GetCollision(size_t id1, size_t id2) {
	// returns true if two colliders are currently colliding
	if (collisionStates.count(id1)) {
		if (collisionStates[id1].count(id2)) {
			return collisionStates[id1][id2] == CollisionState::In || collisionStates[id1][id2] == CollisionState::JustIn;
		}
	}
	return false;
};
void CollisionManager::SetCollision(Collider2D* col1, Collider2D* col2, bool state) {
	// determine the new state
	size_t id1 = col1->id;
	size_t id2 = col2->id;

	CollisionState newState = GetNewCollisionState(id1, id2, state);

	// save the new state
	collisionStates[id1][id2] = newState;
	collisionStates[id2][id1] = newState;

	// save collision vector
	if (state) {
		collisions[id1].push_back(col2);
		collisions[id2].push_back(col1);
	}

	// inform of collision
	DispatchCollisionEvent(col1, col2, newState);
}

void CollisionManager::DispatchCollisionEvent(Collider2D* col1, Collider2D* col2, CollisionState state) {
	switch (state) {
		case CollisionState::In:
			EventDispatcher::Dispatch("CollisionIn", col1, col2);
			EventDispatcher::Dispatch("CollisionIn", col2, col1);
			break;
		case CollisionState::JustIn:
			EventDispatcher::Dispatch("CollisionEnter", col1, col2);
			EventDispatcher::Dispatch("CollisionEnter", col2, col1);
			break;
		case CollisionState::Out:
			EventDispatcher::Dispatch("CollisionOut", col1, col2);
			EventDispatcher::Dispatch("CollisionOut", col2, col1);
			break;
		case CollisionState::JustOut:
			EventDispatcher::Dispatch("CollisionExit", col1, col2);
			EventDispatcher::Dispatch("CollisionExit", col2, col1);
			break;
		default:
			break;
	}
}

bool CollisionManager::GetCollisionIn(size_t id1, size_t id2) {
	// returns true when the collision first happens
	if (collisionStates.count(id1)) {
		if (collisionStates[id1].count(id2)) {
			return collisionStates[id1][id2] == CollisionState::JustIn;
		}
	}
	return false;
};
bool CollisionManager::GetCollisionOut(size_t id1, size_t id2) {
	// return true when the collision first exists
	if (collisionStates.count(id1)) {
		if (collisionStates[id1].count(id2)) {
			return collisionStates[id1][id2] == CollisionState::JustOut;
		}
	}
	return false;
};
CollisionManager::CollisionState CollisionManager::GetCollisionState(size_t id1, size_t id2) {
	// returns the current collision state of two colliders
	if (collisionStates.count(id1)) {
		if (collisionStates[id1].count(id2)) {
			return collisionStates[id1][id2];
		}
	}
	return CollisionState::Out; // default assume not colliding
};

CollisionManager::CollisionState CollisionManager::GetNewCollisionState(size_t id1, size_t id2, bool state) {
	// determine the new collision state based off the current collision state
	// the 'just' state happens for only one frame
	CollisionState currState = GetCollisionState(id1, id2);
	CollisionState newState;
	if (state == true) {
		if (currState == CollisionState::JustIn || currState == CollisionState::In) {
			newState = CollisionState::In;
		}
		else {
			newState = CollisionState::JustIn;
		}
	}
	else {
		if (currState == CollisionState::JustOut || currState == CollisionState::Out) {
			newState = CollisionState::Out;
		}
		else {
			newState = CollisionState::JustOut;
		}
	}
	return newState;
}



std::vector<Collider2D*> CollisionManager::GetCollisions(size_t id1) {
	if (collisions.count(id1)) {
		return collisions[id1];
	}
	return std::vector<Collider2D*>{}; // empty dataset
};
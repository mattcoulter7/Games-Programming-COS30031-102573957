#pragma once


#include "Collider2D.h"

class CollisionManager {
public:
	enum class CollisionState
	{
		JustIn,
		In,
		JustOut,
		Out
	};
	void Update();
	bool GetCollision(size_t id1, size_t id2);
	bool GetCollisionIn(size_t id1, size_t id2);
	bool GetCollisionOut(size_t id1, size_t id2);
	void SetCollision(Collider2D* col1, Collider2D* col2,bool state);
	void DispatchCollisionEvent(Collider2D* col1, Collider2D* col2, CollisionState state);
	std::vector<Collider2D*> GetCollisions(size_t id1);
private:
	CollisionState GetCollisionState(size_t id1, size_t id2);
	CollisionState GetNewCollisionState(size_t id1, size_t id2,bool state);
	std::map<size_t, std::map<size_t, CollisionState>> collisionStates; // state of the collision between two object
	std::map<size_t, std::vector<Collider2D*>> collisions; // map between one object and everything it is colliding with
};
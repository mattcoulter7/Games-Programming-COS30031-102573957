#pragma once

#include "System.h"

#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "RigidBody2D.h"
#include "Transform2D.h"
#include "Debug.h"
#include "CollisionHistory.h"

class Collider2DSystem : public System {
public:
	Collider2DSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
private:
	bool TestCircleCircle(CircleCollider* col1, CircleCollider* col2);
	bool TestCircleRectangle(CircleCollider* col1, RectangleCollider* col2);
	bool TestRectangleRectangle(RectangleCollider* col1, RectangleCollider* col2);
	void ResolveCollision(Collider2D* col1, Collider2D* col2);
	void UpdateColliderPosition(Collider2D* col);

	CollisionHistory _collisionHistory;
};
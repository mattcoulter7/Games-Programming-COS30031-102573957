#pragma once

#include "ECS.h"

#include "Transform2D.h"
#include "RigidBody2D.h"

#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "BoxCollider.h"
#include "PolygonCollider.h"
#include "Collider2DTransformer.h"
#include "ScreenCollider.h"
#include "GJK.h"

class Collider2DSystem : public System {
public:
	Collider2DSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
	Collider2DTransformer transformer;
	GJK gjk;
private:
	bool TestCollision(Collider2D* col1, Collider2D* col2); // GJK algoithm that works for most things
	bool TestCollision(CircleCollider* col1, CircleCollider* col2); // override for circle -> circle checking
	bool HandleScreenCollision(ScreenCollider* col); // override for circle -> circle checking
	void ResolveCollision(Collider2D* col1, LineCollider* col2);
	void ResolveCollision(Collider2D* col1, Collider2D* col2);
};
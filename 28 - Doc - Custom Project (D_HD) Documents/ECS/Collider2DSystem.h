#pragma once

#include "System.h"

#include "GJK.h"
#include "Collider2DTransformer.h"
#include "CollisionManager.h"

class CircleCollider;
class ScreenCollider;
class LineCollider;
class PointCollider;

class Collider2DSystem : public System {
public:
	Collider2DSystem();
	Collider2DSystem(json obj);
	~Collider2DSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
	CollisionManager collisionManager; // holds collisions states
	Collider2DTransformer transformer;
	GJK gjk;
private:
	void AddEventListeners() override;
	bool TestCollision(Collider2D* col1, Collider2D* col2); // GJK algoithm that works for most things
	bool TestCollision(CircleCollider* col1, CircleCollider* col2); // override for circle -> circle checking as this is faster
	bool TestCollision(CircleCollider* col1, PointCollider* col2); // override for circle -> point checking as this is faster
};
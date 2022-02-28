#pragma once

#include "Collider2DSystem.h"

#include "ECS.h"

Collider2DSystem::Collider2DSystem() : System() {
	_collisionHistory = CollisionHistory();
}
void Collider2DSystem::Update(double dt) {
	// stores local history 
	_collisionHistory.Reset();

	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<CircleCollider*> ccs = cm->GetComponents<CircleCollider>(); // circles
	std::vector<RectangleCollider*> rcs = cm->GetComponents<RectangleCollider>(); // rectangles

	// update the collider positions (must be done before doing comparisons)
	for (CircleCollider* col : ccs) {
		UpdateColliderPosition(col);
	}
	for (RectangleCollider* col : rcs) {
		// update the collider
		UpdateColliderPosition(col);
	}

	// ---------- CIRCLES ---------- //
	for (CircleCollider* col1 : ccs) {
		// collisions with other circles
		for (CircleCollider* col2 : ccs) {
			bool collision = TestCircleCircle(col1, col2);
			_collisionHistory.Set(col1, col2, collision); // save history

			// handle the collision
			if (collision) {
				ResolveCollision(col1, col2);
			}
		}

		// collisions with other circles
		for (RectangleCollider* col2 : rcs) {
			bool collision = TestCircleRectangle(col1, col2);
			_collisionHistory.Set(col1, col2, collision); // save history

			// handle the collision
			if (collision) {
				ResolveCollision(col1, col2);
			}
		}
	}

	// ---------- RECTANGLES ---------- //
	for (RectangleCollider* col1 : rcs) {
		// collisions with other rectangles
		for (RectangleCollider* col2 : rcs) {
			bool collision = TestRectangleRectangle(col1, col2);
			_collisionHistory.Set(col1, col2, collision); // save history

			// handle the collision
			if (collision) {
				ResolveCollision(col1, col2);
			}
		}

		// collisions with circles
		for (CircleCollider* col2 : ccs) {
			bool collision = TestCircleRectangle(col2, col1);
			_collisionHistory.Set(col1, col2, collision); // save history

			// handle the collision
			if (collision) {
				ResolveCollision(col1, col2);
			}
		}
	}
}

bool Collider2DSystem::TestCircleCircle(CircleCollider* col1, CircleCollider* col2) {
	// cannot collide with it self
	if (col1->entityid == col2->entityid) return false;

	// utilise history for performance optimisation
	if (_collisionHistory.Checked(col1, col2)) {
		return _collisionHistory.Collided(col1, col2);
	}

	Vector2 toCol2 = Vector2{ col2->position.x - col1->position.x,col2->position.y - col1->position.y };
	float requiredCollisionDist = col1->radius + col2->radius;
	float magnitude = toCol2.magnitude();
	return (magnitude <= requiredCollisionDist);
};

bool Collider2DSystem::TestRectangleRectangle(RectangleCollider* col1, RectangleCollider* col2) {
	// cannot collide with it self
	if (col1->entityid == col2->entityid) return false;

	// utilise history for performance optimisation
	if (_collisionHistory.Checked(col1, col2)) {
		return _collisionHistory.Collided(col1, col2);
	}
	//https://www.geeksforgeeks.org/find-two-rectangles-overlap/
	// gets the bottom left and top right points of both colliders
	Vector2 l1 = col1->position;
	Vector2 l2 = col2->position;
	Vector2 r1 = col1->position;
	r1.x += col1->width;
	r1.y -= col1->height;
	Vector2 r2 = col2->position;
	r2.x += col2->width;
	r2.y -= col2->height;

	// the line cannot have positive overlap
	if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x || l2.y == r2.y) {
		return false;
	}

	// If one rectangle is on left side of other
	if (l1.x >= r2.x || l2.x >= r1.x) {
		return false;
	}

	// If one rectangle is above other
	if (r1.y >= l2.y || r2.y >= l1.y) {
		return false;
	}
	return true;
};

bool Collider2DSystem::TestCircleRectangle(CircleCollider* col1, RectangleCollider* col2) {
	// cannot collide with it self
	if (col1->entityid == col2->entityid) return false;

	// utilise history for performance optimisation
	if (_collisionHistory.Checked(col1, col2)) {
		return _collisionHistory.Collided(col1, col2);
	}
	float cx = col1->position.x;
	float cy = col1->position.y;
	float radius = col1->radius;
	float rx = col2->position.x;
	float ry = col2->position.y;
	float rw = col2->width;
	float rh = col2->height;

	//http://www.jeffreythompson.org/collision-detection/circle-rect.php
	// temporary variables to set edges for testing
	float testX = cx;
	float testY = cy;

	// which edge is closest?
	if (cx < rx)         testX = rx;      // test left edge
	else if (cx > rx + rw) testX = rx + rw;   // right edge
	if (cy < ry)         testY = ry;      // top edge
	else if (cy > ry + rh) testY = ry + rh;   // bottom edge

	// get distance from closest edges
	float distX = cx - testX;
	float distY = cy - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the radius, collision!
	if (distance <= radius) {
		return true;
	}
	return false;
}

void Collider2DSystem::UpdateColliderPosition(Collider2D* col) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	Transform2D* tf = cm->GetComponent<Transform2D>(col->entityid);
	if (tf == nullptr) return;

	col->position.x = tf->position.x + col->offset.x;
	col->position.y = tf->position.y + col->offset.y;
};

void Collider2DSystem::ResolveCollision(Collider2D* col1, Collider2D* col2) {
	std::cout << "Collider: (" << col1->id << ", " << col1->entityid << ") collided with Collider: (" << col2->id << ", " << col2->entityid << ")" << std::endl;
};


void Collider2DSystem::Render(SDL_Renderer* renderer) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<CircleCollider*> ccs = cm->GetComponents<CircleCollider>(); // circles
	std::vector<RectangleCollider*> rcs = cm->GetComponents<RectangleCollider>(); // rectangles

	for (CircleCollider* col : ccs) {
		Debug::Instance()->RenderCircle(renderer, col->position.x, col->position.y,col->radius);
	}
	for (RectangleCollider* col : rcs) {
		Debug::Instance()->RenderRect(renderer,col->position.x,col->position.y,col->width,col->height);
	}
}
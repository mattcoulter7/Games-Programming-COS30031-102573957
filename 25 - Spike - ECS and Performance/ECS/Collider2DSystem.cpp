#pragma once

#include "Collider2DSystem.h"
#include "Debug.h"

#include "Render2DSystem.h"

Collider2DSystem::Collider2DSystem() : System() {
}
void Collider2DSystem::Update(double dt) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<BoxCollider*> bcs = cm->GetComponents<BoxCollider>(); // box colliders (creates line colliders)
	for (BoxCollider* col : bcs) {
		transformer.SetWorldPosition(col);
		transformer.SetBoxLines(col); // incase the width or height is changed
	}

	std::vector<CircleCollider*> ccs = cm->GetComponents<CircleCollider>(); // circles
	std::vector<RectangleCollider*> rcs = cm->GetComponents<RectangleCollider>(); // rectangles
	std::vector<PolygonCollider*> pcs = cm->GetComponents<PolygonCollider>(); // polygons
	std::vector<LineCollider*> lcs = cm->GetComponents<LineCollider>(); // lines

	// update the collider positions (must be done before doing comparisons)
	for (CircleCollider* col : ccs) {
		transformer.SetWorldPosition(col);
	}
	for (LineCollider* col : lcs) {
		transformer.SetWorldPosition(col);
		transformer.SetLinePoints(col); // incase the x,y values changed
		transformer.SetWorldPoints(col);
		transformer.SetEdges(col);
	}
	for (RectangleCollider* col : rcs) {
		transformer.SetWorldPosition(col);
		transformer.SetRectanglePoints(col); // incase the width or height is changed
		transformer.SetWorldPoints(col);
		transformer.SetEdges(col);
	}
	for (PolygonCollider* col : pcs) {
		transformer.SetWorldPosition(col);
		transformer.SetWorldPoints(col);
		transformer.SetEdges(col);
	}

	// ---------- CIRCLES ---------- //
	for (CircleCollider* col1 : ccs) {
		for (CircleCollider* col2 : ccs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
		for (RectangleCollider* col2 : rcs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
		for (PolygonCollider* col2 : pcs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
		for (LineCollider* col2 : lcs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
	}
	// ---------- RECTANGLES ---------- //
	for (RectangleCollider* col1 : rcs) {
		for (RectangleCollider* col2 : rcs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
		for (PolygonCollider* col2 : pcs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
		for (LineCollider* col2 : lcs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
	}
	// ---------- POLYGONS ---------- //
	for (PolygonCollider* col1 : pcs) {
		for (PolygonCollider* col2 : pcs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
		for (LineCollider* col2 : lcs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
	}
	// ---------- LINES ---------- //
	for (LineCollider* col1 : lcs) {
		for (LineCollider* col2 : lcs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
	}
	// ---------- SCREEN COLLIDERS  ---------- //
	std::vector<ScreenCollider*> scs = cm->GetComponents<ScreenCollider>(); // screen colliders
	for (ScreenCollider* col : scs) {
		HandleScreenCollision(col);
	}
}

bool Collider2DSystem::TestCollision(CircleCollider* col1, CircleCollider* col2) {
	// cannot collide with it self
	if (col1->entityid == col2->entityid) return false;

	Vector2 toCol2 = Vector2{ col2->position.x - col1->position.x,col2->position.y - col1->position.y };
	float requiredCollisionDist = col1->radius + col2->radius;
	float magnitude = toCol2.magnitude();
	return (magnitude <= requiredCollisionDist);
};

bool Collider2DSystem::TestCollision(Collider2D* col1, Collider2D* col2) {
	// cannot collide with it self
	if (col1->entityid == col2->entityid) return false;
	return gjk.TestCollision(col1, col2);
}

bool Collider2DSystem::HandleScreenCollision(ScreenCollider* col){
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

void Collider2DSystem::ResolveCollision(Collider2D* col1, LineCollider* col2) {
	//std::cout << "Collider: (" << col1->id << ", " << col1->entityid << ") collided with Collider: (" << col2->id << ", " << col2->entityid << ")" << std::endl;

	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	RigidBody2D* rb1 = cm->GetComponent<RigidBody2D>(col1->entityid);
	if (rb1 == nullptr) return;
	Vector2 d = rb1->velocity;
	Vector2 n = Vector2::Left(col2->edges[0]);
	n.Normalise();

	float dn = 2 * Vector2::DotProduct(d, n);
	rb1->velocity = d - (n * dn);
}

void Collider2DSystem::ResolveCollision(Collider2D* col1, Collider2D* col2) {
	//std::cout << "Collider: (" << col1->id << ", " << col1->entityid << ") collided with Collider: (" << col2->id << ", " << col2->entityid << ")" << std::endl;
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	RigidBody2D* rb1 = cm->GetComponent<RigidBody2D>(col1->entityid);
	RigidBody2D* rb2 = cm->GetComponent<RigidBody2D>(col2->entityid);
	
};

void Collider2DSystem::Render(SDL_Renderer* renderer) {
	return;
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<CircleCollider*> ccs = cm->GetComponents<CircleCollider>(); // circles
	std::vector<RectangleCollider*> rcs = cm->GetComponents<RectangleCollider>(); // rectangles
	std::vector<PolygonCollider*> pcs = cm->GetComponents<PolygonCollider>(); // rectangles
	std::vector<LineCollider*> lcs = cm->GetComponents<LineCollider>(); // lines

	for (CircleCollider* col : ccs) {
		Debug::Instance()->RenderCircle(renderer, col->position.x, col->position.y,col->radius);
	}
	for (RectangleCollider* col : rcs) {
		Debug::Instance()->RenderPolygon(renderer, col->worldPts);
	}
	for (PolygonCollider* col : pcs) {
		Debug::Instance()->RenderPolygon(renderer, col->worldPts);
	}
	for (LineCollider* col : lcs) {
		Debug::Instance()->RenderLine(renderer, col->worldPts[0].x, col->worldPts[0].y, col->worldPts[1].x, col->worldPts[1].y);
	}
}
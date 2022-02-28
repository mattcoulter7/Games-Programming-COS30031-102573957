#pragma once

#include "Collider2DSystem.h"

#include "Debug.h"

Collider2DSystem::Collider2DSystem() : System() {
}
void Collider2DSystem::Update(double dt) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<CircleCollider*> ccs = cm->GetComponents<CircleCollider>(); // circles
	std::vector<RectangleCollider*> rcs = cm->GetComponents<RectangleCollider>(); // rectangles
	std::vector<PolygonCollider*> pcs = cm->GetComponents<PolygonCollider>(); // polygons

	// update the collider positions (must be done before doing comparisons)
	for (CircleCollider* col : ccs) {
		transformer.SetWorldPosition(col);
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
	}
	// ---------- POLYGONS ---------- //
	for (PolygonCollider* col1 : pcs) {
		for (PolygonCollider* col2 : pcs) {
			if (TestCollision(col1, col2)) {
				ResolveCollision(col1, col2);
			}
		}
	}
}

bool Collider2DSystem::TestCollision(Collider2D* col1, Collider2D* col2) {
	// cannot collide with it self
	if (col1->entityid == col2->entityid) return false;
	return gjk.TestCollision(col1, col2);
}

void Collider2DSystem::ResolveCollision(Collider2D* col1, Collider2D* col2) {
	std::cout << "Collider: (" << col1->id << ", " << col1->entityid << ") collided with Collider: (" << col2->id << ", " << col2->entityid << ")" << std::endl;
};

void Collider2DSystem::Render(SDL_Renderer* renderer) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<CircleCollider*> ccs = cm->GetComponents<CircleCollider>(); // circles
	std::vector<RectangleCollider*> rcs = cm->GetComponents<RectangleCollider>(); // rectangles
	std::vector<PolygonCollider*> pcs = cm->GetComponents<PolygonCollider>(); // rectangles

	for (CircleCollider* col : ccs) {
		Debug::Instance()->RenderCircle(renderer, col->position.x, col->position.y,col->radius);
	}
	for (RectangleCollider* col : rcs) {
		Debug::Instance()->RenderPolygon(renderer, col->worldPts);
	}
	for (PolygonCollider* col : pcs) {
		Debug::Instance()->RenderPolygon(renderer, col->worldPts);
	}
}
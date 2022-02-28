#pragma once

#include "Collider2DSystem.h"
#include "ECS.h"

#include "Debug.h"

#include "Render2DSystem.h"

#include "Collider2D.h";
#include "CircleCollider.h";
#include "ScreenCollider.h";
#include "LineCollider.h";
#include "BoxCollider.h";
#include "PointCollider.h";
#include "RectangleCollider.h";
#include "ChunkyLineCollider.h";

Collider2DSystem::Collider2DSystem() : System() {
	AddEventListeners();
}
Collider2DSystem::Collider2DSystem(json obj) : System(obj) {
	AddEventListeners();
}
Collider2DSystem::~Collider2DSystem() {};
void Collider2DSystem::AddEventListeners() {}

void Collider2DSystem::Update(double dt) {
	collisionManager.Update();
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<BoxCollider*> bcs = cm->GetComponents<BoxCollider>(); // box colliders (creates line colliders)
	for (BoxCollider* col : bcs) {
		transformer.SetWorldPosition(col);
		transformer.SetBoxLines(col); // incase the width or height is changed
	}

	std::vector<CircleCollider*> circleCols = cm->GetComponents<CircleCollider>(); // circles
	std::vector<RectangleCollider*> rectCols = cm->GetComponents<RectangleCollider>(); // rectangles
	std::vector<PolygonCollider*> polyCols = cm->GetComponents<PolygonCollider>(); // polygons
	std::vector<LineCollider*> lineCols = cm->GetComponents<LineCollider>(); // lines
	std::vector<ChunkyLineCollider*> chunkyLineCols = cm->GetComponents<ChunkyLineCollider>(); // chunky line colliders
	std::vector<PointCollider*> ptCols = cm->GetComponents<PointCollider>(); // points

	// update the collider positions (must be done before doing comparisons)
	for (CircleCollider* col : circleCols) {
		transformer.SetWorldPosition(col);
	}
	for (LineCollider* col : lineCols) {
		transformer.SetWorldPosition(col);
		transformer.SetLinePoints(col); // incase the x,y values changed
		transformer.SetWorldPoints(col);
		transformer.SetEdges(col);
	}
	for (ChunkyLineCollider* col : chunkyLineCols) {
		transformer.SetWorldPosition(col);
		transformer.SetChunkyLinePoints(col);
		transformer.SetWorldPoints(col);
		transformer.SetEdges(col);
	}
	for (RectangleCollider* col : rectCols) {
		transformer.SetWorldPosition(col);
		transformer.SetRectanglePoints(col); // incase the width or height is changed
		transformer.SetWorldPoints(col);
		transformer.SetEdges(col);
	}
	for (PolygonCollider* col : polyCols) {
		transformer.SetWorldPosition(col);
		transformer.SetWorldPoints(col);
		transformer.SetEdges(col);
	}
	for (PointCollider* col : ptCols) {
		transformer.SetWorldPosition(col);
	}

	// run the collision checks IMPORTANT: DO NOT RUN THE SAME COLLISION CHECK TWICE!
	// ---------- CIRCLES ---------- //
	for (CircleCollider* col1 : circleCols) {
		for (CircleCollider* col2 : circleCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (RectangleCollider* col2 : rectCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (PolygonCollider* col2 : polyCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (LineCollider* col2 : lineCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (PointCollider* col2 : ptCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (ChunkyLineCollider* col2 : chunkyLineCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
	}
	// ---------- RECTANGLES ---------- //
	for (RectangleCollider* col1 : rectCols) {
		for (RectangleCollider* col2 : rectCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (PolygonCollider* col2 : polyCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (LineCollider* col2 : lineCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (PointCollider* col2 : ptCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (ChunkyLineCollider* col2 : chunkyLineCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
	}
	// ---------- POLYGONS ---------- //
	for (PolygonCollider* col1 : polyCols) {
		for (PolygonCollider* col2 : polyCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (LineCollider* col2 : lineCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (PointCollider* col2 : ptCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (ChunkyLineCollider* col2 : chunkyLineCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
	}
	// ---------- LINES ---------- //
	for (LineCollider* col1 : lineCols) {
		for (LineCollider* col2 : lineCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (PointCollider* col2 : ptCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (ChunkyLineCollider* col2 : chunkyLineCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
	}

	// ---------- POINTS ---------- //
	for (PointCollider* col1 : ptCols) {
		for (PointCollider* col2 : ptCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
		for (ChunkyLineCollider* col2 : chunkyLineCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
	}

	// ---------- CHUNKY LINE COLS ---------- //
	for (ChunkyLineCollider* col1 : chunkyLineCols) {
		for (ChunkyLineCollider* col2 : chunkyLineCols) {
			collisionManager.SetCollision(col1, col2, TestCollision(col1, col2));
		}
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
bool Collider2DSystem::TestCollision(CircleCollider* col1, PointCollider* col2) {
	// cannot collide with it self
	if (col1->entityid == col2->entityid) return false;

	Vector2 toCol2 = col1->position.To(col2->position);
	float magnitude = toCol2.magnitude();
	return (magnitude <= col1->radius);
};

bool Collider2DSystem::TestCollision(Collider2D* col1, Collider2D* col2) {
	// cannot collide with it self
	if (col1->entityid == col2->entityid) return false;
	return gjk.TestCollision(col1, col2);
}

void Collider2DSystem::Render(SDL_Renderer* renderer) {
	if (ECS::ECS_ENGINE()->debug) {
		ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
		std::vector<CircleCollider*> ccs = cm->GetComponents<CircleCollider>(); // circles
		std::vector<RectangleCollider*> rcs = cm->GetComponents<RectangleCollider>(); // rectangles
		std::vector<PolygonCollider*> pcs = cm->GetComponents<PolygonCollider>(); // rectangles
		std::vector<LineCollider*> lcs = cm->GetComponents<LineCollider>(); // lines
		std::vector<ChunkyLineCollider*> chunkyLineCols = cm->GetComponents<ChunkyLineCollider>(); // chunky lines

		for (CircleCollider* col : ccs) {
			Debug::Instance()->RenderCircle(renderer, col->position.x, col->position.y, col->radius);
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
		for (ChunkyLineCollider* col : chunkyLineCols) {
			Debug::Instance()->RenderPolygon(renderer, col->worldPts);
		}
	}
}
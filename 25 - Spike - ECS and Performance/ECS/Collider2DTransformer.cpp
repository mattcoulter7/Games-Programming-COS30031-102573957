#include "Collider2DTransformer.h"


// set world position of collider based on transform
void Collider2DTransformer::SetWorldPosition(Collider2D* col) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	Transform2D* tf = cm->GetComponent<Transform2D>(col->entityid);
	Vector2 newPos = col->position;
	if (tf != nullptr) {
		newPos = tf->position;
	}
	newPos += col->offset; // offset from entities position
	col->position = newPos;
};
// transform relative points to world points based on transform
void Collider2DTransformer::SetRectanglePoints(RectangleCollider* col) {
	// bottom left
	col->localPts[0].x = 0;
	col->localPts[0].y = 0;
	// top left
	col->localPts[1].x = 0;
	col->localPts[1].y = -col->height;
	// top right
	col->localPts[2].x = col->width; // up
	col->localPts[2].y = -col->height; // up
	// bottom right
	col->localPts[3].x = col->width; // up
	col->localPts[3].y = 0; // up
};
void Collider2DTransformer::SetLinePoints(LineCollider* col) {
	// pt1
	col->localPts[0].x = col->x1;
	col->localPts[0].y = col->y1;
	// pt2
	col->localPts[1].x = col->x2;
	col->localPts[1].y = col->y2;
}
// transform relative points to world points based on transform
void Collider2DTransformer::SetWorldPoints(PolygonCollider* col) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	Transform2D* tf = cm->GetComponent<Transform2D>(col->entityid);
	col->worldPts.clear();
	if (tf == nullptr) {
		col->worldPts = col->localPts; // no transformations are being applied
	}
	else {
		for (Vector2 pt : col->localPts) {
			col->worldPts.push_back(tf->TransformPoint(pt) + col->offset);
		}
	}
};

void Collider2DTransformer::SetBoxLines(BoxCollider* col) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	for (int i = 0; i < 4; i++) {
		if (col->lines[i] == nullptr) {
			col->lines[i] = cm->AddComponent<LineCollider>(col->entityid);
		}
	}

	// bottom left
	col->lines[0]->x1 = 0;
	col->lines[0]->y1 = 0;
	col->lines[3]->x2 = 0;
	col->lines[3]->y2 = 0;

	// top left
	col->lines[0]->x2 = 0;
	col->lines[0]->y2 = col->height;
	col->lines[1]->x1 = 0;
	col->lines[1]->y1 = col->height;

	// top right
	col->lines[1]->x2 = col->width;
	col->lines[1]->y2 = col->height;
	col->lines[2]->x1 = col->width;
	col->lines[2]->y1 = col->height;

	// bottom right
	col->lines[2]->x2 = col->width;
	col->lines[2]->y2 = 0;
	col->lines[3]->x1 = col->width;
	col->lines[3]->y1 = 0;
};
// the the edge vectors that join each of the worl points
void Collider2DTransformer::SetEdges(PolygonCollider* col) {
	Vector2 p1;
	Vector2 p2;
	col->edges.clear(); //reset all edges
	std::vector<Vector2> worldPts = col->worldPts;
	for (size_t i = 0; i < worldPts.size(); i++) {
		p1 = worldPts[i];
		if (i >= worldPts.size() - 1) {
			p2 = worldPts[0];
		}
		else {
			p2 = worldPts[i + 1];
		}
		col->edges.push_back(p2 - p1);
	}
}
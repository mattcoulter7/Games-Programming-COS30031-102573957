#pragma once

#include "RouteCreatorSystem.h"

#include "ECS.h"
#include "Input.h"
#include "Debug.h"

#include "CursorSystem.h"

#include "Transform2D.h"
#include "Train.h"
#include "ChunkyLineCollider.h"
#include "TrainStation.h"

RouteCreatorSystem::RouteCreatorSystem() : System() {
	AddEventListeners();
};
RouteCreatorSystem::RouteCreatorSystem(json obj) : System(obj) {
	trainPrefabId = obj["trainPrefabId"].is_null() ? trainPrefabId : obj["trainPrefabId"];
	routePrefabId = obj["routePrefabId"].is_null() ? routePrefabId : obj["routePrefabId"];
	AddEventListeners();
}
RouteCreatorSystem::~RouteCreatorSystem() {

};
void RouteCreatorSystem::AddEventListeners() {
	EventDispatcher::AddEventListener("ColliderMouseEnter", &RouteCreatorSystem::MouseEnter, this);
	EventDispatcher::AddEventListener("ColliderMouseExit", &RouteCreatorSystem::MouseExit, this);
	EventDispatcher::AddEventListener("MouseMove", &RouteCreatorSystem::MouseMove, this);

	EventDispatcher::AddEventListener("InputUp", &RouteCreatorSystem::HandleStopModification, this);
	EventDispatcher::AddEventListener("ColliderInput", &RouteCreatorSystem::HandleModifyCurrentRoute, this);
	EventDispatcher::AddEventListener("ColliderInputDown", &RouteCreatorSystem::HandleStartNewRoute, this);
	EventDispatcher::AddEventListener("ColliderInputDown", &RouteCreatorSystem::HandleDestroyRoute, this);
}
void RouteCreatorSystem::Update(double dt) {}
void RouteCreatorSystem::MouseEnter(Collider2D* col) {
	if (currentRoute == nullptr) return;
	if (intent == Intent::Remove && col->position != currentRoute->nodes[currentRoute->nodes.size() - 1]) {
		intent = Intent::Add;
	}
}
void RouteCreatorSystem::MouseExit(Collider2D* col) {
	intent = (intent == Intent::Add) ? Intent::Remove : Intent::Add;
}
void RouteCreatorSystem::MouseMove(Vector2 pos, Vector2 vel) {
	// ensure intent is add if there is no current route
	if (currentRoute == nullptr) {
		intent = Intent::Add;
	}
	else {
		// cancel the route if the amount of nodes becomes 0
		if (currentRoute->nodes.size() == 0) {
			CancelRoute();
		}
	}
}

void RouteCreatorSystem::HandleStartNewRoute(Uint8 input, Collider2D* col) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	TrainStation* station = cm->GetComponent<TrainStation>(col->entityid);
	if (station == nullptr) return;
	// mouse click to start a new route
	if (input == 1 && currentRoute == nullptr) {
		// add a new route
		Entity* entity = ECS::ECS_ENGINE()->GetInstantiator()->Instantiate(routePrefabId);
		currentRoute = cm->GetComponent<Route>(entity->GetId());
	}
};

void RouteCreatorSystem::HandleModifyCurrentRoute(Uint8 input,bool state,Collider2D* col) {// ensure there is a current route to modify
	// ensure collider is a station
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	Transform2D* trainStationTf = cm->GetComponent<Transform2D>(col->entityid);
	TrainStation* station = cm->GetComponent<TrainStation>(col->entityid);
	if (station == nullptr) return;

	// holding the left mouse button down
	if (currentRoute == nullptr) return;
	if (input == 1 && state == true) {
		// if intending to remove
		if (intent == Intent::Remove) {
			// remove if the station is the last station in the route
			if (currentRoute->nodes.size() > 0 && trainStationTf->position == currentRoute->nodes[currentRoute->nodes.size() - 1]) {
				currentRoute->nodes.pop_back();
			}
		}

		// if intending to add
		if (intent == Intent::Add) {
			// set to false if a particular station cannot be added to the route
			bool canAdd = true;

			// RULE 1: don't link to an already linked node
			for (Vector2 pt : currentRoute->nodes) {
				if (pt == trainStationTf->position) {
					canAdd = false;
				}
			}

			// RULE 2: A route can return the path back to the start
			if (currentRoute->nodes.size() >= 2 && trainStationTf->position == currentRoute->nodes[0]) {
				canAdd = true;
			}

			// RULE 3: can't connect any further once connected back to start
			if (currentRoute->nodes.size() > 2 && currentRoute->nodes[currentRoute->nodes.size() - 1] == currentRoute->nodes[0]) {
				// finish path
				return SaveRoute();
			}

			// add the point to the path
			if (canAdd) {
				currentRoute->nodes.push_back(trainStationTf->position);
			}
		}
	}
};

void RouteCreatorSystem::HandleStopModification(Uint8 input) {
	// let go of the mouse button
	if (currentRoute == nullptr) return;
	if (input == 1)
	{
		// clear if there is more than 1 node
		if (currentRoute->nodes.size() > 1) {
			SaveRoute();
		}
		else {
			CancelRoute();
		}
	}
}

void RouteCreatorSystem::HandleDestroyRoute(Uint8 input,Collider2D* col){
	if (input == 3) {
		// ensure collider is attached to a route
		ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
		Route* route = cm->GetComponent<Route>(col->entityid);
		if (route == nullptr) return;

		// destroy any trains on the route
		std::vector<Train*> trains = cm->GetComponents<Train>();
		for (Train* train : trains) {
			if (train->routeid == route->id) {
				ECS::ECS_ENGINE()->GetInstantiator()->Destroy(train->entityid);
			}
		}

		// destroy the route entity and all of its components
		ECS::ECS_ENGINE()->GetInstantiator()->Destroy(route->entityid);
	}
}

void RouteCreatorSystem::SaveRoute() {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	currentRoute->inUse = true;
	currentRoute->shapedRoute = GetShapedRoute(currentRoute->nodes);

	// add colliders for reinteracting with the existing route
	for (int i = 0; i < currentRoute->shapedRoute.size() - 1; i++) {
		Vector2 start = currentRoute->shapedRoute[i];
		Vector2 end = currentRoute->shapedRoute[i+1];

		ChunkyLineCollider* col = cm->AddComponent<ChunkyLineCollider>(currentRoute->entityid);
		col->x1 = start.x;
		col->x2 = end.x;
		col->y1 = start.y;
		col->y2 = end.y;
		col->width = 5;
	}

	// add a new train to the route
	Entity* train = ECS::ECS_ENGINE()->GetInstantiator()->Instantiate(trainPrefabId, currentRoute->nodes[0]);
	Train* trainComponent = cm->GetComponent<Train>(train->GetId());
	trainComponent->routeid = currentRoute->id;

	// remove reference
	currentRoute = nullptr;
};

void RouteCreatorSystem::CancelRoute() {
	// destroy the route entity and all of its components
	ECS::ECS_ENGINE()->GetInstantiator()->Destroy(currentRoute->entityid);
	currentRoute = nullptr;
};

std::vector<Vector2> RouteCreatorSystem::GetShapedRoute(std::vector<Vector2> pts) {
	// create the train path
	std::vector<Vector2> trainPath;
	for (int i = 0; i < pts.size(); ++i) {
		Vector2 pt = pts[i];
		trainPath.push_back(pt);
		if (i < pts.size() - 1) {
			Vector2 connectingPt = pts[i + 1];
			Vector2 toConnectingPt = pt.To(connectingPt);

			float minValue = std::abs(toConnectingPt.x) < std::abs(toConnectingPt.y) ? toConnectingPt.x : toConnectingPt.y;

			float xMidPt = minValue;
			float yMidPt = xMidPt;

			if (toConnectingPt.x > 0 && toConnectingPt.y < 0 && std::abs(toConnectingPt.y) > std::abs(toConnectingPt.x)) {
				yMidPt *= -1;
			}
			else if (toConnectingPt.x > 0 && toConnectingPt.y < 0 && std::abs(toConnectingPt.x) > std::abs(toConnectingPt.y)) {
				xMidPt *= -1;
			}
			else if (toConnectingPt.y > 0 && toConnectingPt.x < 0 && std::abs(toConnectingPt.y) > std::abs(toConnectingPt.x)) {
				yMidPt *= -1;
			}
			else if (toConnectingPt.y > 0 && toConnectingPt.x < 0 && std::abs(toConnectingPt.x) > std::abs(toConnectingPt.y)) {
				xMidPt *= -1;
			}


			Vector2 middlePt = pt + Vector2{ xMidPt ,yMidPt };

			trainPath.push_back(middlePt);
		}
	}
	return trainPath;
}
void RouteCreatorSystem::Render(SDL_Renderer* renderer) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<Route*> routes = cm->GetComponents<Route>();

	if (currentRoute != nullptr) {
		if (currentRoute->nodes.size() == 0) return;

		std::vector<Vector2> pts = currentRoute->nodes;
		pts.push_back(Input::Instance()->GetMousePos());
		std::vector<Vector2> trainPath = GetShapedRoute(pts);

		ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
		Debug::Instance()->RenderOpenPolygon(renderer, trainPath);
	}
	return;
	// render each route
	for (Route* route : routes) {
		if (route == currentRoute) continue;
		if (!route->inUse) continue;
		Debug::Instance()->RenderOpenPolygon(renderer, route->shapedRoute);


		// render the end of the route
		if (route->nodes[0] == route->nodes[route->nodes.size() - 1]) {
			// render 1 t shape
		}
		else {
			// render t shape at either end
			Vector2 first = route->shapedRoute[1].To(route->shapedRoute[0]).GetNormalised();
			first *= 40.0;
			first = route->nodes[0] + first;
			Debug::Instance()->RenderLine(renderer, route->nodes[0].x, route->nodes[0].y, first.x, first.y);
		}
	}

}
#include "TrainSystem.h"

#include "ECS.h"
#include "Input.h"
#include "Debug.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Transform2D.h"
#include "RigidBody2D.h"
#include "Train.h"
#include "Route.h"
#include "TrainStation.h"

TrainSystem::TrainSystem() : System() {
	AddEventListeners();
}
TrainSystem::TrainSystem(json obj) : System(obj) {
	AddEventListeners();
}
TrainSystem::~TrainSystem() {}

void TrainSystem::AddEventListeners() {
	EventDispatcher::AddEventListener("CollisionEnter", &TrainSystem::DispatchTrainArriveAtStation, this);
	EventDispatcher::AddEventListener("CollisionExit", &TrainSystem::DispatchTrainDepartFromStation, this);
	EventDispatcher::AddEventListener("CollisionIn", &TrainSystem::DispatchTrainAtStation, this);
}

void TrainSystem::DispatchTrainArriveAtStation(Collider2D* stationCol, Collider2D* trainCol) {
	// ensure the colliders are of type train and station
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	EntityManager* em = ECS::ECS_ENGINE()->GetEntityManager();

	// ensure it is a train
	Train* train = cm->GetComponent<Train>(trainCol->entityid);
	if (train == nullptr) return;

	// get it is a trainstation
	TrainStation* trainStation = cm->GetComponent<TrainStation>(stationCol->entityid);
	if (trainStation == nullptr) return;

	train->state = Train::State::AtStation;
	EventDispatcher::Dispatch("TrainArriveAtStation", train, trainStation);
};

void TrainSystem::DispatchTrainDepartFromStation(Collider2D* stationCol, Collider2D* trainCol) {
	// ensure the colliders are of type train and station
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	EntityManager* em = ECS::ECS_ENGINE()->GetEntityManager();

	// ensure it is a train
	Train* train = cm->GetComponent<Train>(trainCol->entityid);
	if (train == nullptr) return;

	// get it is a trainstation
	TrainStation* trainStation = cm->GetComponent<TrainStation>(stationCol->entityid);
	if (trainStation == nullptr) return;

	EventDispatcher::Dispatch("TrainDepartFromStation", train, trainStation);
};

void TrainSystem::DispatchTrainAtStation(Collider2D* stationCol, Collider2D* trainCol) {
	// ensure the colliders are of type train and station
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	EntityManager* em = ECS::ECS_ENGINE()->GetEntityManager();

	// ensure it is a train
	Train* train = cm->GetComponent<Train>(trainCol->entityid);
	if (train == nullptr) return;

	// get it is a trainstation
	TrainStation* trainStation = cm->GetComponent<TrainStation>(stationCol->entityid);
	if (trainStation == nullptr) return;

	EventDispatcher::Dispatch("TrainAtStation", train, trainStation);
};

void TrainSystem::Update(double dt) {
	// move the trains along their respective route
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<Train*> trains = cm->GetComponents<Train>();

	for (Train* train : trains) {
		Transform2D* trainTf = cm->GetComponent<Transform2D>(train->entityid);
		RigidBody2D* trainRb = cm->GetComponent<RigidBody2D>(train->entityid);
		// ensure route is valid
		Route* route = cm->GetComponentById<Route>(train->routeid);
		if (route == nullptr) {
			ECS::ECS_ENGINE()->GetInstantiator()->Destroy(train->entityid);
			continue;
		}

		if (train->state == Train::State::AtStation) {
			trainRb->velocity.x = 0;
			trainRb->velocity.y = 0;
		}
		else {
			// ensure the train stays on the path
			if (train->targetIndex == route->shapedRoute.size()) {
				if (route->shapedRoute[route->shapedRoute.size() - 1] == route->shapedRoute[0]) {
					// it's a circle!
					train->targetIndex = 0;
				}
				else {
					// turn around and go back the other way!
					train->targetIndex = train->targetIndex - 1;
					train->direction = -1;
				}
			}
			if (train->targetIndex == -1 && train->direction == -1) {
				// flip back to normal direction if turned around
				train->targetIndex = 1;
				train->direction = 1;
			}

			// approach the target
			Vector2 target = route->shapedRoute[train->targetIndex];
			Vector2 toTarget = trainTf->position.To(target);
			float dist = toTarget.magnitude();
			if (dist < 2) {
				train->targetIndex += 1 * train->direction;
			}
			toTarget.Normalise();
			trainTf->rotation = -Vector2::FindAngle(toTarget, Vector2{ 1,0 }); // rotate in the correct direction
			toTarget *= train->maxSpeed;
			trainRb->velocity = toTarget; // move to the target
		}
	}
}

void TrainSystem::Render(SDL_Renderer* renderer) {

}
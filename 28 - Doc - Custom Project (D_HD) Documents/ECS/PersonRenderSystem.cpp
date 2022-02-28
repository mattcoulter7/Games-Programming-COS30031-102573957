#include "PersonRenderSystem.h"

#include "ECS.h"

#include "Time.h"
#include "rand_extension.hpp"

#include "Train.h"
#include "TrainStation.h"
#include "Transform2D.h"
#include "SpriteRenderer2D.h"

/*
	positions people to be in the correct position relative the train/station
*/

PersonRenderSystem::PersonRenderSystem() {
	AddEventListeners();
};
PersonRenderSystem::PersonRenderSystem(json obj) {
	AddEventListeners();
};
PersonRenderSystem::~PersonRenderSystem() {

};

void PersonRenderSystem::Update(double dt) {
	// set the position of the person to that of the station/train
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();

	// update position of people at the stations
	std::vector<TrainStation*> stations = cm->GetComponents<TrainStation>();
	for (TrainStation* station : stations) {
		Transform2D* stationTf = cm->GetComponent<Transform2D>(station->entityid);
		std::vector<Person*> people = GetAtStation(station);
		SetPeoplePositions(stationTf, people);
	}

	// update the position of people on trains
	std::vector<Train*> trains = cm->GetComponents<Train>();
	for (Train* train : trains) {
		Transform2D* trainTf = cm->GetComponent<Transform2D>(train->entityid);
		std::vector<Person*> people = GetOnTrain(train);
		SetPeoplePositions(trainTf, people);
	}
};


void PersonRenderSystem::SetPeoplePositions(Transform2D* tf, std::vector<Person*> people) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	int currStep = 1;
	for (Person* person : people) {
		Transform2D* personTf = cm->GetComponent<Transform2D>(person->entityid);
		SpriteRenderer2D* personRenderer = cm->GetComponent<SpriteRenderer2D>(person->entityid);
		personTf->position = Vector2{ tf->position.x + currStep * 16, tf->position.y - 16 };
		++currStep;
	}
}


void PersonRenderSystem::Render(SDL_Renderer* renderer) {

};

void PersonRenderSystem::AddEventListeners() {};


std::vector<Person*> PersonRenderSystem::GetOnTrain(Train* train) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<Person*> everyone = cm->GetComponents<Person>();

	std::vector<Person*> people;

	for (Person* person : everyone) {
		if (person->state != Person::State::OnTrain) continue; // cannot pickup someone who isn't at a station
		if (person->trainId != train->id) continue; // can only pickup people at the current train station
		people.push_back(person);
	}

	return people;
};
std::vector<Person*> PersonRenderSystem::GetAtStation(TrainStation* trainStation) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<Person*> everyone = cm->GetComponents<Person>();

	std::vector<Person*> people;

	for (Person* person : everyone) {
		if (person->state != Person::State::WaitingAtStation) continue; // cannot pickup someone who isn't at a station
		if (person->trainStationId != trainStation->id) continue; // can only pickup people at the current train station
		people.push_back(person);
	}

	return people;
};
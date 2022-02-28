#include "PersonPickupDropoffSystem.h"

#include "ECS.h"

#include "Time.h"
#include "rand_extension.hpp"

#include "Train.h"
#include "TrainStation.h"
#include "Transform2D.h"

/*
	Handles picking up people from train stations onto stations
	Handles dropping off people from train stations onto stations
*/

PersonPickupDropoffSystem::PersonPickupDropoffSystem() {
	AddEventListeners();
};
PersonPickupDropoffSystem::PersonPickupDropoffSystem(json obj) {
	AddEventListeners();
};
PersonPickupDropoffSystem::~PersonPickupDropoffSystem() {

};

void PersonPickupDropoffSystem::Update(double dt) {};
void PersonPickupDropoffSystem::Render(SDL_Renderer* renderer) {};
void PersonPickupDropoffSystem::AddEventListeners() {
	EventDispatcher::AddEventListener("TrainAtStation", &PersonPickupDropoffSystem::HandlePickupsAndDropoffs, this);
};


std::vector<Person*> PersonPickupDropoffSystem::GetDropoffPeople(Train* train, TrainStation* trainStation) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<Person*> everyone = cm->GetComponents<Person>();

	std::vector<Person*> people;

	for (Person* person : everyone) {
		if (person->state != Person::State::OnTrain) continue; // cannot dropoff someone who isn't on a train
		if (person->type != trainStation->type) continue; // can only dropoff of the same type
		if (person->trainStationId == trainStation->id) continue; // cannot drop them off where they were picked up
		if (person->trainId != train->id) continue; // cannot drop off someone who is on a different train
		people.push_back(person);
	}

	return people;
};

std::vector<Person*> PersonPickupDropoffSystem::GetPickupPeople(Train* train, TrainStation* trainStation) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<Person*> everyone = cm->GetComponents<Person>();

	std::vector<Person*> people;

	for (Person* person : everyone) {
		if (person->state != Person::State::WaitingAtStation) continue; // cannot pickup someone who isn't at a station
		if (person->trainStationId != trainStation->id) continue; // can only pickup people at the current train station
		if (train->currCapacity + people.size() >= train->maxCapacity) continue; // cannot hold more than max people
		people.push_back(person);
	}

	return people;
};

void PersonPickupDropoffSystem::HandlePickupsAndDropoffs(Train* train,TrainStation* trainStation) {
	// only run when they are in the at station state
	if (train->state != Train::State::AtStation) return;

	// cannot run next procees until last one has gotten off
	double currentTime = Time::Instance()->runTime;
	if (currentTime < train->nextTransfer) return;

	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();

	std::vector<Person*> toPickup = GetPickupPeople(train, trainStation);
	std::vector<Person*> toDropoff = GetDropoffPeople(train, trainStation);

	// correct the state
	train->state = (toPickup.size() > 0 || toDropoff.size() > 0) ? Train::State::AtStation : Train::State::Moving;

	// handle dropoffs (respectfully people get off of the train first)
	for (Person* person : toDropoff) {
		// handle dropoffs
		if (currentTime >= train->nextTransfer) {
			HandleDropoff(train, trainStation, person);
		}
	}

	// handle pickups
	for (Person* person : toPickup) {
		// handle dropoffs
		if (currentTime >= train->nextTransfer) {
			HandlePickup(train, trainStation, person);
		}
	}
};

void PersonPickupDropoffSystem::HandlePickup(Train* train, TrainStation* trainStation, Person* person) {
	person->state = Person::State::OnTrain; // put them on the train

	person->trainId = train->id; // specify the train they are on

	std::cout << "person picked up" << std::endl;

	// update the next spawn
	train->nextTransfer = Time::Instance()->runTime + train->personTransferSpeed;
	++train->currCapacity;
};

void PersonPickupDropoffSystem::HandleDropoff(Train* train, TrainStation* trainStation, Person* person) {
	EventDispatcher::Dispatch("PersonDroppedOff", person); // send the message to be picked up by score system
	ECS::ECS_ENGINE()->GetInstantiator()->Destroy(person->entityid); // destory the person as no longer needed

	std::cout << "person dropped off" << std::endl;

	// update the next spawn
	train->nextTransfer = Time::Instance()->runTime + train->personTransferSpeed;
	--train->currCapacity;
};
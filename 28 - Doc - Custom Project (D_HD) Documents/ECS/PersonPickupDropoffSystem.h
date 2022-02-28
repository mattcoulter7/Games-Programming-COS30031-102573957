#pragma once

#include "System.h"

#include "Person.h"
/*
	Handles picking up people from train stations onto stations
	Handles dropping off people from train stations onto stations
*/

class Train;
class TrainStation;
class PersonPickupDropoffSystem : public System {
public:
	PersonPickupDropoffSystem();
	PersonPickupDropoffSystem(json obj);
	~PersonPickupDropoffSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
	void AddEventListeners() override;
	void HandlePickupsAndDropoffs(Train* train,TrainStation* trainStation);
	void HandlePickup(Train* train, TrainStation* trainStation, Person* person);
	void HandleDropoff(Train* train, TrainStation* trainStation, Person* person);
private:
	std::vector<Person*> GetPickupPeople(Train* train, TrainStation* trainStation);
	std::vector<Person*> GetDropoffPeople(Train* train, TrainStation* trainStation);
};
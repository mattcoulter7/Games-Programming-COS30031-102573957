#pragma once

#include "System.h"

#include "Person.h"
/*
	Handles picking up people from train stations onto stations
	Handles dropping off people from train stations onto stations
*/

class Train;
class TrainStation;
class Transform2D;
class PersonRenderSystem : public System {
public:
	PersonRenderSystem();
	PersonRenderSystem(json obj);
	~PersonRenderSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
	void AddEventListeners() override;
private:
	void SetPeoplePositions(Transform2D* tf,std::vector<Person*> people);
	std::vector<Person*> GetOnTrain(Train* train);
	std::vector<Person*> GetAtStation(TrainStation* trainStation);
};
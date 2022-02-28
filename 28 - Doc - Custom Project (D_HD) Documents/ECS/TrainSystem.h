#pragma once

#include "System.h"

#include "Collider2D.h"

class TrainSystem : public System {
public:
	TrainSystem();
	TrainSystem(json obj);
	~TrainSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
	void DispatchTrainArriveAtStation(Collider2D* stationCol, Collider2D* trainCol);
	void DispatchTrainDepartFromStation(Collider2D* stationCol, Collider2D* trainCol);
	void DispatchTrainAtStation(Collider2D* stationCol, Collider2D* trainCol);
private:
	void AddEventListeners() override;
};
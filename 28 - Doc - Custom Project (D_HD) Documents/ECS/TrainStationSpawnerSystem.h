#include "System.h"

class TrainStationSpawnerSystem : public System {
public:
	TrainStationSpawnerSystem();
	TrainStationSpawnerSystem(json obj);
	~TrainStationSpawnerSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
private:
	void AddEventListeners() override;
	size_t trainStationSpawnerPrefabId = -1;
};
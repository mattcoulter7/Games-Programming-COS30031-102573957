#include "TrainStationSpawnerSystem.h"

#include "ECS.h"
#include "Input.h"
#include "Debug.h"

#include "Spawner.h"
#include "TrainStation.h"
#include "Person.h"

#include "Time.h"
#include "rand_extension.hpp"
#include "Transform2D.h"

TrainStationSpawnerSystem::TrainStationSpawnerSystem() : System() {
	AddEventListeners();
}

TrainStationSpawnerSystem::TrainStationSpawnerSystem(json obj) : System(obj) {
	trainStationSpawnerPrefabId = obj["trainStationSpawnerPrefabId"].is_null() ? trainStationSpawnerPrefabId : obj["trainStationSpawnerPrefabId"];
	AddEventListeners();
};
TrainStationSpawnerSystem::~TrainStationSpawnerSystem() {

};
void TrainStationSpawnerSystem::AddEventListeners() {}
void TrainStationSpawnerSystem::Update(double dt) {
	EntityManager* em = ECS::ECS_ENGINE()->GetEntityManager();
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<RandomSpawner*> trainStationSpawners = cm->GetComponents<RandomSpawner>();

	float currentTime = Time::Instance()->runTime;

	for (RandomSpawner* trainStationSpawner : trainStationSpawners) {
		Entity* trainStationEntity = em->GetEntity(trainStationSpawner->entityid);
		if (trainStationEntity->prefabid != trainStationSpawnerPrefabId) continue;
		
		if (currentTime >= trainStationSpawner->nextSpawn) {
			// spawn a train station
			size_t spawnPrefabId = trainStationSpawner->spawnPrefabIds[rand_extension::between(0, trainStationSpawner->spawnPrefabIds.size() - 1)];
			Entity* trainStationEntity = ECS::ECS_ENGINE()->GetInstantiator()->Instantiate(spawnPrefabId);

			Transform2D* tf = cm->GetComponent<Transform2D>(trainStationEntity->GetId());
			tf->position.x = rand_extension::between(0, 600);
			tf->position.y = rand_extension::between(0, 400);

			// update the next spawn
			trainStationSpawner->nextSpawn = currentTime + rand_extension::between(trainStationSpawner->minSpawnInterval, trainStationSpawner->maxSpawnInterval);

			std::cout << "spawned 1 train station" << std::endl;
		}
	}
}
void TrainStationSpawnerSystem::Render(SDL_Renderer* renderer) {

}
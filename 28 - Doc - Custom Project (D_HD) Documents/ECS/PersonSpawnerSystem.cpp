#include "PersonSpawnerSystem.h"

#include "ECS.h"
#include "Input.h"
#include "Debug.h"

#include "Spawner.h"
#include "TrainStation.h"
#include "Person.h"

#include "Time.h"
#include "rand_extension.hpp"

PersonSpawnerSystem::PersonSpawnerSystem() : System() {
	AddEventListeners();
}

PersonSpawnerSystem::PersonSpawnerSystem(json obj) : System(obj) {
	AddEventListeners();
};
PersonSpawnerSystem::~PersonSpawnerSystem() {

};
void PersonSpawnerSystem::AddEventListeners() {}
void PersonSpawnerSystem::Update(double dt) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	std::vector<RandomSpawner*> personSpawners = cm->GetComponents<RandomSpawner>();
	for (RandomSpawner* personSpawner : personSpawners) {
		TrainStation* trainStation = cm->GetComponent<TrainStation>(personSpawner->entityid);
		if (trainStation == nullptr) continue;
		float currentTime = Time::Instance()->runTime;
		if (currentTime >= personSpawner->nextSpawn) {
			// spawn a person
			size_t spawnPrefabId = personSpawner->spawnPrefabIds[rand_extension::between(0, personSpawner->spawnPrefabIds.size() - 1)];
			Entity* personEntity = ECS::ECS_ENGINE()->GetInstantiator()->Instantiate(spawnPrefabId);
			Person* person = cm->GetComponent<Person>(personEntity->GetId());
			person->trainStationId = trainStation->id;
			
			// update the next spawn
			personSpawner->nextSpawn = currentTime + rand_extension::between(personSpawner->minSpawnInterval, personSpawner->maxSpawnInterval);

			std::cout << "spawned 1 person" << std::endl;
		}
	}
}
void PersonSpawnerSystem::Render(SDL_Renderer* renderer) {

}
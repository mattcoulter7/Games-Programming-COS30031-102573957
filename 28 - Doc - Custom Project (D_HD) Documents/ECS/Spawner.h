#pragma once

#include "BaseComponent.h"

#include "Time.h"

/*
    Generic Spawner
*/

struct RandomSpawner : public BaseComponent {
    RandomSpawner() : BaseComponent() {}
    RandomSpawner(const RandomSpawner& obj) : BaseComponent(obj) {
        minSpawnInterval = obj.minSpawnInterval;
        maxSpawnInterval = obj.maxSpawnInterval;
        spawnPrefabIds = obj.spawnPrefabIds;
    };
    RandomSpawner(json obj) : BaseComponent(obj) {
        minSpawnInterval = obj["minSpawnInterval"].is_null() ? minSpawnInterval : obj["minSpawnInterval"];
        maxSpawnInterval = obj["maxSpawnInterval"].is_null() ? maxSpawnInterval : obj["maxSpawnInterval"];
        if (!obj["spawnPrefabIds"].is_null()) {
            for (auto& id : obj["spawnPrefabIds"]) {
                spawnPrefabIds.push_back(id);
            }
        }
    } // json constructor
    ~RandomSpawner() {}
    BaseComponent* Clone() {
        return new RandomSpawner(*this);
    }
    float minSpawnInterval = 1000;
    float maxSpawnInterval = 5000;
    float nextSpawn = 0;
    std::vector<size_t> spawnPrefabIds; // id of whatever is going to be spawned
};
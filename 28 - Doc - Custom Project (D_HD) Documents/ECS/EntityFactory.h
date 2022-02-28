#pragma once

#include <string>

#include "Entity.h"

#include "json.hpp"
using json = nlohmann::json;

/*
	handles creation of entities only. Entities are not saved into the EntityManager at this stage
*/
class Entity;
class EntityFactory {
public:
	Entity* Create();
	Entity* CreateFromJson(json obj);
	Entity* CreateFromPrefab(size_t prefabid);
	static EntityFactory* Instance();
private:
	static EntityFactory _instance;
};
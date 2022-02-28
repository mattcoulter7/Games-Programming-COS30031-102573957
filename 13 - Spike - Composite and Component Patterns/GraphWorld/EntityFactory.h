#pragma once

#include "Entity.h"
#include "json.hpp"

#include "ComponentFactory.h"

using json = nlohmann::json;

class EntityFactory {
public:
	Entity* CreateEntity(json entity);
	static EntityFactory* Instance();
private:
	static EntityFactory m_entityFactory;
};
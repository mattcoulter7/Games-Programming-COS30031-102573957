#pragma once

#include "EntityFactory.h"

class EntityManager {
public:
	~EntityManager() {
		for (auto& pair : _entities) {
			delete pair.second;
		}
	}
	Entity* AddEntity() {
		Entity* entity = EntityFactory::Instance()->Create();
		_entities[entity->GetId()] = entity;
		return entity;
	};
	Entity* AddEntityFromJson(json obj) {
		Entity* entity = EntityFactory::Instance()->CreateFromJson(obj);
		_entities[entity->GetId()] = entity;
		return entity;
	};
	Entity* AddEntityFromPrefab(size_t prefabid) {
		Entity* entity = EntityFactory::Instance()->CreateFromPrefab(prefabid);
		_entities[entity->GetId()] = entity;
		return entity;
	};
	void RemoveEntity(size_t entityid) {
		Entity* entity = _entities[entityid];
		if (entity != nullptr) {
			delete entity;
			_entities.erase(entityid);
		}
	}
	Entity* GetEntity(size_t entityid) {
		return _entities[entityid];
	}
private:
	std::map<size_t,Entity*> _entities;
};
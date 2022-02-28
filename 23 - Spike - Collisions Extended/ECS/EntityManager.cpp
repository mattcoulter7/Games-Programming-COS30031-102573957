#pragma once

#include "Entity.h"

class EntityManager {
public:
	template<typename ...Args>
	Entity* AddEntity(Args... args) {
		Entity* entity = new Entity(args...);
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
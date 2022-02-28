#include "EntityFactory.h"

EntityFactory EntityFactory::m_entityFactory;
Entity* EntityFactory::CreateEntity(json entity) {
	EntityType type = (EntityType)entity["Type"];
	Entity* newEntity = new Entity(type);

	json childrenJSON = entity["Children"];
	for (json child : childrenJSON) {
		newEntity->AddChild(CreateEntity(child)); // recursive loop
	}

	json componentJSON = entity["Components"];
	for (json component : componentJSON) {
		newEntity->AddComponent(ComponentFactory::Instance()->CreateComponent(component));
	}

	return newEntity;
};

EntityFactory* EntityFactory::Instance() {
	return &m_entityFactory;
}
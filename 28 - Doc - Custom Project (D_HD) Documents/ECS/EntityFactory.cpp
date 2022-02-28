#include "EntityFactory.h"

#include "ECS.h"

Entity* EntityFactory::Create() {
	return new Entity();
}
Entity* EntityFactory::CreateFromJson(json obj) {
	return new Entity(obj);
}
Entity* EntityFactory::CreateFromPrefab(size_t prefabid) {
	PrefabManager* prefabManager = ECS::ECS_ENGINE()->GetPrefabManager();
	Prefab* prefab = prefabManager->GetPrefab(prefabid);

	return new Entity(prefab);
}

EntityFactory* EntityFactory::Instance() {
	return &_instance;
}
EntityFactory EntityFactory::_instance;
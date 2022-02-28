#include "Instantiator.h"

#include "ECS.h"
#include "Transform2D.h"

Instantiator::Instantiator() {};
Entity* Instantiator::Instantiate(size_t prefabid) {
	ECS* ecs = ECS::ECS_ENGINE();

	// create the entity
	Entity* entity = ecs->GetEntityManager()->AddEntityFromPrefab(prefabid);

	// create the components against the entity
	ecs->GetComponentManager()->AddComponentsFromPrefab(entity->GetId(), prefabid);

	return entity;
};
Entity* Instantiator::Instantiate(size_t prefabid,Vector2 pos) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();

	// create the tntiy
	Entity* entity = Instantiate(prefabid);

	// set the position
	Transform2D* tf = cm->GetComponent<Transform2D>(entity->GetId());
	tf->position = pos;

	return entity;
};

void Instantiator::Destroy(size_t entityid) {
	ECS::ECS_ENGINE()->GetEntityManager()->RemoveEntity(entityid);
	ECS::ECS_ENGINE()->GetComponentManager()->RemoveComponents(entityid);
};
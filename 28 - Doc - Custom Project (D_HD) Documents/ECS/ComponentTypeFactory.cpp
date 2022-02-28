#include "ComponentTypeFactory.h"

#include "ECS.h"

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "LineCollider.h"
#include "PointCollider.h"
#include "PolygonCollider.h"
#include "RectangleCollider.h"
#include "ScreenCollider.h"
#include "Cursor.h"
#include "RigidBody2D.h"
#include "Route.h"
#include "SpriteRenderer2D.h"
#include "Train.h"
#include "Transform2D.h"
#include "ChunkyLineCollider.h"
#include "Spawner.h"
#include "TrainStation.h"
#include "Person.h"


ComponentTypeFactory::ComponentTypeFactory() {
	RegisterFactory<BoxCollider>("BoxCollider");
	RegisterFactory<CircleCollider>("CircleCollider");
	RegisterFactory<LineCollider>("LineCollider");
	RegisterFactory<PointCollider>("PointCollider");
	RegisterFactory<PolygonCollider>("PolygonCollider");
	RegisterFactory<RectangleCollider>("RectangleCollider");
	RegisterFactory<ScreenCollider>("ScreenCollider");
	RegisterFactory<Cursor>("Cursor");
	RegisterFactory<RigidBody2D>("RigidBody2D");
	RegisterFactory<Route>("Route");
	RegisterFactory<SpriteRenderer2D>("SpriteRenderer2D");
	RegisterFactory<Train>("Train");
	RegisterFactory<Transform2D>("Transform2D");
    RegisterFactory<ChunkyLineCollider>("ChunkyLineCollider");
    RegisterFactory<RandomSpawner>("RandomSpawner");
    RegisterFactory<TrainStation>("TrainStation");
    RegisterFactory<Person>("Person");
}
ComponentTypeFactory::~ComponentTypeFactory() {
    for (auto& pair : _factoriesByName) {
        delete pair.second;
    }
}

// create a component based off a type
BaseComponent* ComponentTypeFactory::Create(std::string type)
{
    return _factoriesByName.at(type)->Create();
}

// create a component from given json
BaseComponent* ComponentTypeFactory::CreateFromJson(json obj)
{
    std::string type = obj["_type"];
    return _factoriesByName.at(type)->CreateFromJson(obj);
}

std::vector<BaseComponent*> ComponentTypeFactory::CreateFromJsonArray(json obj) {
    std::vector<BaseComponent*> components;
    // create the components from json
    for (json& comp : obj) {
        components.push_back(ComponentTypeFactory::Instance()->CreateFromJson(comp));
    }
    return components;
}

// create all components for a given prefab
std::vector<BaseComponent*> ComponentTypeFactory::CreateFromPrefab(size_t prefabid) {
    PrefabManager* prefabManager = ECS::ECS_ENGINE()->GetPrefabManager();
    Prefab* prefab = prefabManager->GetPrefab(prefabid);

	// clone each of the components
    std::vector<BaseComponent*> components;
    for (BaseComponent* c : prefab->GetComponents()) {
        components.push_back(c->Clone());
    }

    return components;
}
ComponentTypeFactory* ComponentTypeFactory::Instance() {
    return &_instance;
}
ComponentTypeFactory ComponentTypeFactory::_instance;
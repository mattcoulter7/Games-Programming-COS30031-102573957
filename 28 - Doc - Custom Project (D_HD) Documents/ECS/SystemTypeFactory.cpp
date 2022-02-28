#include "SystemTypeFactory.h"

#include "ECS.h"

#include "Render2DSystem.h"
#include "PhysicsSystem.h"
#include "Collider2DSystem.h"
#include "RouteCreatorSystem.h"
#include "TrainSystem.h"
#include "CursorSystem.h"
#include "PersonSpawnerSystem.h"
#include "PersonPickupDropoffSystem.h"
#include "PersonRenderSystem.h"
#include "TrainStationSpawnerSystem.h"

SystemTypeFactory::SystemTypeFactory() {
    RegisterFactory<Render2DSystem>("Render2DSystem");
    RegisterFactory<PhysicsSystem>("PhysicsSystem");
    RegisterFactory<Collider2DSystem>("Collider2DSystem");
    RegisterFactory<RouteCreatorSystem>("RouteCreatorSystem");
    RegisterFactory<TrainSystem>("TrainSystem");
    RegisterFactory<CursorSystem>("CursorSystem");
    RegisterFactory<PersonSpawnerSystem>("PersonSpawnerSystem");
    RegisterFactory<PersonPickupDropoffSystem>("PersonPickupDropoffSystem");
    RegisterFactory<PersonRenderSystem>("PersonRenderSystem");
    RegisterFactory<TrainStationSpawnerSystem>("TrainStationSpawnerSystem");
}
SystemTypeFactory::~SystemTypeFactory() {
    for (auto& pair : _factoriesByName) {
        delete pair.second;
    }
}

// create a component based off a type
System* SystemTypeFactory::Create(std::string type)
{
    return _factoriesByName.at(type)->Create();
}

// create a component from given json
System* SystemTypeFactory::CreateFromJson(json obj)
{
    std::string type = obj["_type"];
    return _factoriesByName.at(type)->CreateFromJson(obj);
}

SystemTypeFactory* SystemTypeFactory::Instance() {
    return &_instance;
}
SystemTypeFactory SystemTypeFactory::_instance;
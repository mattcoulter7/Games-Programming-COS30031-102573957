#include "ComponentFactory.h"

#include "ComponentPickupable.h"
#include "ComponentDropable.h"

ComponentFactory ComponentFactory::m_componentFactory;

Component* ComponentFactory::CreateComponent(json component) {
	ComponentType type = (ComponentType)component["Type"];
	switch (type)
	{
		case ComponentType::Pickupable:
			return new ComponentPickupable();
		case ComponentType::Dropable:
			return new ComponentDropable();
		default:
			break;
	}
	return nullptr;
}

ComponentFactory* ComponentFactory::Instance() {
	return &m_componentFactory;
}
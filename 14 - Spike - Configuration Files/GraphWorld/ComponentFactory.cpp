#include "ComponentFactory.h"

#include "ComponentPickupable.h"
#include "ComponentDropable.h"
#include "ComponentUnlock.h"
#include "ComponentLocked.h"
#include "ComponentOpenable.h"

ComponentFactory ComponentFactory::m_componentFactory;

Component* ComponentFactory::CreateComponent(json component) {
	ComponentType type = (ComponentType)component["Type"];
	Component* c = nullptr;
	switch (type)
	{
		case ComponentType::Pickupable:
			c = new ComponentPickupable(component);
			break;
		case ComponentType::Dropable:
			c = new ComponentDropable(component);
			break;
		case ComponentType::Unlock:
			c = new ComponentUnlock(component);
			break;
		case ComponentType::Locked:
			c = new ComponentLocked(component);
			break;
		case ComponentType::Openable:
			c = new ComponentOpenable(component);
			break;
		default:
			break;
	}
	return c;
}

ComponentFactory* ComponentFactory::Instance() {
	return &m_componentFactory;
}
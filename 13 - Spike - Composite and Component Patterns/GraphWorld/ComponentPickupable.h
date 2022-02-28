#include "Component.h"

class ComponentPickupable : public Component {
public:
	ComponentPickupable() : Component(ComponentType::Pickupable) {};
};
#include "Component.h"

class ComponentPickupable : public Component {
public:
	ComponentPickupable(json component) : Component(ComponentType::Pickupable) {
	
	};
};
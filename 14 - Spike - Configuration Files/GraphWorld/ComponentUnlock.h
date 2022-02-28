#include "Component.h"

// give an entity the ability to unlock something with a unique key
class ComponentUnlock : public Component {
public:
	ComponentUnlock(json component) : Component(ComponentType::Unlock) {
		key = component["key"];
	};
	std::string key;
};
#include "Component.h"

enum class LockedState{
	Unlocked,
	Locked
};
// give an entity the ability to unlock something with a unique key
class ComponentLocked : public Component {
public:
	ComponentLocked(json component) : Component(ComponentType::Locked) {
		key = component["key"];
	};
	std::string key; // the unique key that allows this to be unlockeds
	LockedState state = LockedState::Locked;
};
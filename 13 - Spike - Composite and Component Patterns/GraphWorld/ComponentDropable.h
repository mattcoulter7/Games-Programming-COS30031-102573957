#include "Component.h"

class ComponentDropable : public Component {
public:
	ComponentDropable() : Component(ComponentType::Dropable) {};
};
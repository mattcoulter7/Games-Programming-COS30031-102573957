#include "Component.h"

class ComponentDropable : public Component {
public:
	ComponentDropable(json component) : Component(ComponentType::Dropable) {
	};
};
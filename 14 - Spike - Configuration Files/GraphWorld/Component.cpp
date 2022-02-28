#include "Component.h"

Component::Component(ComponentType type) {
	_type = type;
};
ComponentType Component::GetType() {
	return _type;
};

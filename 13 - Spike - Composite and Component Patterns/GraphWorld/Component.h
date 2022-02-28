#pragma once

#include <map>

#include "ComponentType.h"

class Component {
public:
	Component(ComponentType type);
	ComponentType GetType();
private:
	ComponentType _type;
};
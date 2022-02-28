#pragma once

#include <map>
#include <string>

#include "json.hpp"
using json = nlohmann::json;

#include "ComponentType.h"

class Component {
public:
	Component(ComponentType type);
	ComponentType GetType();
private:
	ComponentType _type;
};
#pragma once

#include <string>
#include <vector>

#include "BaseComponent.h"

class Entity {
public:
	Entity();
	size_t GetId();
private:
	std::vector<Entity*> _children;

	size_t _id;
	static size_t current_id; // added
};
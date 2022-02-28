#pragma once

#include "Entity.h"

size_t Entity::current_id = 0;
Entity::Entity() {
	_id = current_id++;
}
size_t Entity::GetId() {
	return _id;
}
#pragma once

#include <string>
#include <vector>
#include <map>

class Entity {
public:
	Entity();
	size_t GetId();
private:
	size_t _id;
	static size_t current_id; // added
};
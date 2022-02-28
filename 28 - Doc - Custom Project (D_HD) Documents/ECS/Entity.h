#pragma once

#include <string>
#include <vector>
#include <map>

#include "Prefab.h"

class Entity {
public:
	Entity() {
		_id = current_id++;
		prefabid = -1;
	}
	Entity(json obj) {
		_id = current_id++;
		prefabid = -1;
		_name = obj["name"].is_null() ? _name : obj["name"];
	}
	Entity(Prefab* prefab) {
		_id = current_id++;
		_name = prefab->GetName() + " (clone)"; // the real unity wayyy
		prefabid = prefab->GetId();
	}
	std::string GetName() {
		return _name;
	}
	size_t GetId() {
		return _id;
	}
	size_t prefabid;
private:
	std::vector<Entity*> children;
	std::string _name;
	size_t _id;
	static size_t current_id; // added
};
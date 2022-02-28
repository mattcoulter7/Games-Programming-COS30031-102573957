#pragma once

#include <string>
#include <map>
#include <vector>

#include "Vector2.h"

#include "json.hpp"
using json = nlohmann::json;

/*
	maintain ids for components for file reading
*/


struct BaseComponent {
	BaseComponent() {
		// default creation against an entity
		entityid = -1;
		id = current_id++;
		prefabcomponentid = -1;
	};
	BaseComponent(const BaseComponent& obj) {
		// copy constructor
		entityid = -1; // needs to be assigned afterwards
		id = current_id++; // should be a new id
		prefabcomponentid = obj.prefabcomponentid;
	};
	BaseComponent(json obj) {
		// creation from json data (from file/prefab)
		entityid = -1; // needs to be assigned afterwards
		id = current_id++;
		prefabcomponentid = obj["prefabcomponentid"].is_null() ? -1 : obj["prefabcomponentid"];
	}
	virtual ~BaseComponent() {};
	virtual BaseComponent* Clone() = 0; // invokes copy constructor without needing to specify type

	bool active = true;
	size_t prefabcomponentid = -1; // saved for linked entity components to prefab components
	size_t entityid = -1;
	size_t id = -1;

	static size_t current_id; // added
};
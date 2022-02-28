#pragma once

#include <typeinfo>
#include <string>
#include <map>
#include <vector>
#include "Vector2.h"


struct BaseComponent {
	BaseComponent(size_t entityId) {
		entityid = entityId;
		id = current_id++;
	};
	virtual ~BaseComponent() {};

	bool active = true;
	size_t entityid;
	size_t id;
	
	// type as id for storing components
	template<class T>
	static size_t GetType() {
		return typeid(T).hash_code();
	}
	static size_t current_id; // added
};
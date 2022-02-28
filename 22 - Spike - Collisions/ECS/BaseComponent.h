#pragma once

#include <typeinfo>

struct BaseComponent {
	BaseComponent() {
		id = current_id++;
	};
	virtual ~BaseComponent() {};

	bool active = true;
	size_t entityid = -1;
	size_t id;
	
	// type as id for storing components
	template<class T>
	static size_t GetType() {
		return typeid(T).hash_code();
	}
	static size_t current_id; // added
};
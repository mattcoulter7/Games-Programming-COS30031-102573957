#pragma once

#include "ComponentManager.h"
#include <vector>
#include <typeinfo>

class System {
public:
	System();
	virtual void Update(ComponentManager* cm) = 0;
	virtual void Render(ComponentManager* cm) = 0;

	template<class T>
	static size_t GetType() {
		return typeid(T).hash_code();
	}
};
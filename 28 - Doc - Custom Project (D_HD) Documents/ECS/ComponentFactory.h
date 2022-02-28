#pragma once

#include "BaseComponent.h"

class ComponentFactoryBase { // base class so template classes can be stored
public:
	virtual BaseComponent* Create() = 0;
	virtual BaseComponent* CreateFromJson(json obj) = 0;
};

template<typename T>
class ComponentFactory : public ComponentFactoryBase {
public:
	BaseComponent* Create() override {
		return new T();
	}
	BaseComponent* CreateFromJson(json obj) override {
		return new T(obj);
	}
};
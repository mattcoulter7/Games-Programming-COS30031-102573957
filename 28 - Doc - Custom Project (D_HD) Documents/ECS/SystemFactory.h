#pragma once

#include "System.h"

class SystemFactoryBase { // base class so template classes can be stored
public:
	virtual System* Create() = 0;
	virtual System* CreateFromJson(json obj) = 0;
};

template<typename T>
class SystemFactory : public SystemFactoryBase {
public:
	System* Create() override {
		return new T();
	}
	System* CreateFromJson(json obj) override {
		return new T(obj);
	}
};
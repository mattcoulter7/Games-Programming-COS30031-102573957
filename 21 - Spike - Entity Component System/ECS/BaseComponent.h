#pragma once

#include <typeinfo>

struct BaseComponent {
	bool active = true;
	size_t entityid;
	BaseComponent();
	virtual ~BaseComponent(); //even virtual destructor makes a class polymorphic!
	
	template<class T>
	static size_t GetType() {
		return typeid(T).hash_code();
	}
};
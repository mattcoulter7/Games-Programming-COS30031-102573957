#pragma once

#include "BaseComponent.h"

class Prefab {
public:
	Prefab(size_t id,std::string name,std::vector<BaseComponent*> components) {
		_id = id;
		_name = name;
		_components = components;
	}
	~Prefab() {
		for (BaseComponent* comp : _components) {
			delete comp;
		}
		delete rawJSON;
	}
	size_t GetId() {
		return _id;
	}
	std::string GetName() {
		return _name;
	}
	std::vector<BaseComponent*> GetComponents() {
		return _components;
	}
	BaseComponent* GetComponent(size_t prefabcomponentid) {
		for (BaseComponent* component : _components) {
			if (component->prefabcomponentid == prefabcomponentid) {
				return component;
			}
		}
		return nullptr;
	}
	json* rawJSON;
private:
	std::string _name;
	size_t _id;
	std::vector<BaseComponent*> _components;
};
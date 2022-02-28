#pragma once
/*
not divided into 2 files to avoid visual studio error:
Error	LNK2019	unresolved external symbol "public: class PhysicsSystem * __cdecl SystemManager::AddSystem<class PhysicsSystem>(void)" (??$AddSystem@VPhysicsSystem@@@SystemManager@@QEAAPEAVPhysicsSystem@@XZ) referenced in function main	SDLTemplate	D:\Users\Matt\Documents\GitHub\cos30031-102573957\22 - Spike - Collisions\SDLTemplate\main.obj	1
*/
#include <string>
#include <map>
#include <vector>

#include "BaseComponent.h"

typedef std::map<size_t, std::vector<BaseComponent*>> ComponentCollection; // map of vectors indexed by class type
class ComponentManager {
public:
	template<class T, typename ...Args>
	T* AddComponent(size_t entityId,Args... args) {
		//get the type for map indexing
		size_t compType = BaseComponent::GetType<T>();

		// create the component
		T* comp = new T(args...);
		comp->entityid = entityId;

		// store it under main colection
		_components[compType].push_back(comp);

		// store it under entity indexed collection
		_entityComponents[entityId][compType].push_back(comp);

		return comp;
	};

	// remove the last of type t from entity
	template <class T>
	void RemoveComponent(size_t entityId) {
		// find the component to remove
		std::vector<T*> entityComponents = GetComponents<T>(entityId);
		if (entityComponents.size() > 0) {
			size_t compType = BaseComponent::GetType<T>();
			// find the element to remove
			T* removeComponent = entityComponents[entityComponents.size() - 1];

			// remove from entity components
			auto entityIt = std::find(entityComponents.begin(), entityComponents.end(), removeComponent);
			if (entityIt != entityComponents.end()) {
				int index = entityIt - entityComponents.begin();
				_entityComponents[entityId][compType].erase(_entityComponents[entityId][compType].begin() + index);
			}

			// remove from all components
			std::vector<T*> allComponents = GetComponents<T>();
			auto componentIt = std::find(allComponents.begin(), allComponents.end(), removeComponent);
			if (componentIt != allComponents.end()) {
				int index = componentIt - allComponents.begin();
				_components[compType].erase(_components[compType].begin() + index);
			}

			delete removeComponent;
		}
	};

	// all components of type
	template <class T>
	std::vector<T*> GetComponents()
	{
		size_t compType = BaseComponent::GetType<T>();
		std::vector<BaseComponent*> components = _components[compType];
		return *(std::vector<T*> *) & components; // ensure vector is casted as correct type
	};

	// all components of type under entity
	template <class T>
	std::vector<T*> GetComponents(size_t entityId)
	{
		size_t compType = BaseComponent::GetType<T>();
		std::vector<BaseComponent*> entityComponents = _entityComponents[entityId][compType];
		return *(std::vector<T*> *) & entityComponents; // ensure vector is casted as correct type
	};

	// first component of type under entity
	template <class T>
	T* GetComponent(size_t entityId)
	{
		std::vector<T*> entityComponents = GetComponents<T>(entityId);
		if (entityComponents.size() > 0) {
			return entityComponents[0];
		}
		return nullptr;
	};
private:
	ComponentCollection _components;
	std::map<size_t, ComponentCollection> _entityComponents;
};

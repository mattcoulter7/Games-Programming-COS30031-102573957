#pragma once

#include "ComponentTypeFactory.h"

typedef std::map<std::type_index, std::vector<BaseComponent*>> ComponentCollection; // map of vectors indexed by class type
class ComponentManager {
public:
	ComponentManager() {
	}
	~ComponentManager() {
		for (auto& pair : _components) {
			for (BaseComponent* comp : pair.second) {
				delete comp;
			}
		}
	}


	// add an initialised component to an entity
	void AddComponent(size_t entityid, BaseComponent* component) {
		component->entityid = entityid;
		std::type_index compType = typeid(*component);

		// store it under main colection
		_components[compType].push_back(component);

		// store it under entity indexed collection
		_entityComponents[entityid][compType].push_back(component);
	}

	// add initialised components to an entity
	void AddComponents(size_t entityid, std::vector<BaseComponent*> components) {
		for (BaseComponent* comp : components) {
			AddComponent(entityid, comp);
		}
	}

	std::vector<BaseComponent*> AddComponentsFromPrefab(size_t entityid, size_t prefabid) {
		std::vector<BaseComponent*> components = ComponentTypeFactory::Instance()->CreateFromPrefab(prefabid);
		AddComponents(entityid, components);
		return components;
	}

	template<class T, typename ...Args>
	T* AddComponent(size_t entityid,Args... args) {
		//get the type for map indexing
		std::type_index compType = typeid(T);

		// create the component
		T* comp = ComponentTypeFactory::Instance()->Create<T>();

		AddComponent(entityid, comp);

		return comp;
	};

	// remove the last of type t from entity
	template <class T>
	void RemoveComponent(size_t entityId) {
		// find the component to remove
		std::vector<T*> entityComponents = GetComponents<T>(entityId);
		if (entityComponents.size() > 0) {
			std::type_index compType = typeid(T);
			// find the element to remove
			T* comp = entityComponents[entityComponents.size() - 1];

			RemoveComponent(comp);
		}
	};

	// remove all components of type T from entity
	template <class T>
	void RemoveComponents() {
		ComponentCollection entityComponents = _entityComponents[entityId][typeid(T)];
		for (T* comp : entityComponents) {
			RemoveComponent(comp);
		}
	}

	// remove all of the components from an entity
	void RemoveComponents(size_t entityId) {
		ComponentCollection entityComponents = _entityComponents[entityId];
		for (auto& pair : entityComponents) {
			for (BaseComponent* comp : pair.second) {
				RemoveComponent(comp);
			}
		}
	}

	// all components of type
	template <class T>
	std::vector<T*> GetComponents()
	{
		std::type_index compType = typeid(T);
		std::vector<BaseComponent*> components = _components[compType];
		return *(std::vector<T*>*) & components; // ensure vector is casted as correct type
	};

	// all components of type under entity
	template <class T>
	std::vector<T*> GetComponents(size_t entityId)
	{
		std::type_index compType = typeid(T);
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

	// first component of type
	template <class T>
	T* GetComponent()
	{
		std::vector<T*> components = GetComponents<T>();
		if (components.size() > 0) {
			return components[0];
		}
		return nullptr;
	};

	// component by component id
	template <class T>
	T* GetComponentById(size_t componentId)
	{
		std::vector<T*> components = GetComponents<T>();
		for (T* comp : components) {
			if (comp->id == componentId) {
				return comp;
			}
		}
		return nullptr;
	};

private:

	void RemoveComponent(BaseComponent* comp) {
		std::type_index compType = typeid(*comp);
		size_t entityId = comp->entityid;

		// remove from entity components
		std::vector<BaseComponent*> entityComponents = _entityComponents[entityId][compType];
		auto entityIt = std::find(entityComponents.begin(), entityComponents.end(), comp);
		if (entityIt != entityComponents.end()) {
			int index = entityIt - entityComponents.begin();
			_entityComponents[entityId][compType].erase(_entityComponents[entityId][compType].begin() + index);
		}

		// remove from all components
		std::vector<BaseComponent*> allComponents = _components[compType];
		auto componentIt = std::find(allComponents.begin(), allComponents.end(), comp);
		if (componentIt != allComponents.end()) {
			int index = componentIt - allComponents.begin();
			_components[compType].erase(_components[compType].begin() + index);
		}

		delete comp;
	}

	ComponentCollection _components;
	std::map<size_t, ComponentCollection> _entityComponents;
};

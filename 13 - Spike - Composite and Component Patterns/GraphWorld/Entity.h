#pragma once

#include <vector>
#include <string>

#include "Component.h"
#include "EntityType.h"

class Component;

class Entity {
public:
	Entity(EntityType type);

	std::vector<Entity*> GetChildren();
	void AddChild(Entity* child);
	EntityType GetType();
	std::string GetLabel();

	std::vector<Component*> GetComponents();
	void AddComponent(Component* component);
	bool HasComponent(ComponentType type);

	static std::vector<std::string> EntityTypeStrings;
private:
	EntityType _type;
	std::vector<Entity*> _children;
	std::vector<Component*> _components;
};
#pragma once

#include <vector>
#include <string>

#include "Component.h"
#include "EntityType.h"

class Component;

class Entity {
public:
	Entity(EntityType type, std::string description);

	std::vector<Entity*> GetChildren();
	void AddChild(Entity* child);
	EntityType GetType();
	std::string GetLabel();
	std::string GetDescription();
	std::string GetContents();

	std::vector<Component*> GetComponents();
	void AddComponent(Component* component);
	bool HasComponent(ComponentType type);
	Component* GetComponent(ComponentType type);

	static std::vector<std::string> EntityTypeStrings;
private:
	std::string _description;
	EntityType _type;
	std::vector<Entity*> _children;
	std::vector<Component*> _components;
};
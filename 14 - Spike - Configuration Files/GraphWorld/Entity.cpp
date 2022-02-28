#include "Entity.h"


Entity::Entity(EntityType type,std::string description) {
	_type = type;
	_description = description;
};

std::vector<Entity*> Entity::GetChildren() {
	return _children;
};
void Entity::AddChild(Entity* child) {
	_children.push_back(child);
};
EntityType Entity::GetType() {
	return _type;
}
std::string Entity::GetLabel() {
	return EntityTypeStrings[(unsigned int)GetType()];
};

std::string Entity::GetDescription() {
	return _description;
};
std::string Entity::GetContents() {
	std::string contents = "";
	for (Entity* e : _children) {
		contents += "*" + e->GetLabel() + ": " + e->GetDescription() + "\n";
	}
	return contents;
};
bool Entity::HasComponent(ComponentType type) {
	for (Component* component : _components) {
		if (component->GetType() == type) {
			return true;
		}
	}
	return false;
};

Component* Entity::GetComponent(ComponentType type) {
	for (Component* component : _components) {
		if (component->GetType() == type) {
			return component;
		}
	}
	return nullptr;
}
void Entity::AddComponent(Component* component) {
	_components.push_back(component);
}
std::vector<Component*> Entity::GetComponents() {
	return _components;
};

std::vector<std::string> Entity::EntityTypeStrings = { "bag","rock","chest","key","gold"};

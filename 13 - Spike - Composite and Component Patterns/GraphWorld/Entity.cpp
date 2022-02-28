#include "Entity.h"


Entity::Entity(EntityType type) {
	_type = type;
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
bool Entity::HasComponent(ComponentType type) {
	for (Component* component : _components) {
		if (component->GetType() == type) {
			return true;
		}
	}
	return false;
};
void Entity::AddComponent(Component* component) {
	_components.push_back(component);
}
std::vector<Component*> Entity::GetComponents() {
	return _components;
};

std::vector<std::string> Entity::EntityTypeStrings = { "bag","rock" };

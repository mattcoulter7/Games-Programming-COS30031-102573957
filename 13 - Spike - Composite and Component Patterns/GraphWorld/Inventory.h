#pragma once

#include <vector>

#include "Entity.h"

class Inventory {
public:
	std::vector<Entity*> GetItems();
	void AddItem(Entity* item);
	void RemoveItem(Entity* item);
	Entity* GetItem(EntityType type);
	Entity* GetItem(std::string label);

private:
	std::vector<Entity*> _items;
};
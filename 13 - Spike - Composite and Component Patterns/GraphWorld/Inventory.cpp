#pragma once

#include "Inventory.h"

std::vector<Entity*> Inventory::GetItems() {
	return _items;
};
void Inventory::AddItem(Entity* item) {
	_items.push_back(item);
};
void Inventory::RemoveItem(Entity* item) {
	_items.erase(
		std::remove_if(_items.begin(), _items.end(), [item](Entity* i) { return i == item; }),
		_items.end()
	);
};
Entity* Inventory::GetItem(EntityType type) {
	for (Entity* item : _items) {
		if (item->GetType() == type) {
			return item;
		}
	}
	return nullptr;
};

int getIndex(std::vector<std::string> vec, std::string val)
{
	auto it = std::find(vec.begin(), vec.end(), val);

	// If element was found
	if (it != vec.end())
	{
		int index = it - vec.begin();
		return index;
	}
	else {
		return -1;
	}
}

Entity* Inventory::GetItem(std::string label) {
	int type = getIndex(Entity::EntityTypeStrings, label);
	if (type == -1) return nullptr;
	return GetItem((EntityType)type);
};
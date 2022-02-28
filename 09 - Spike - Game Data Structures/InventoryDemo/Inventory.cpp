#include "Inventory.h"
#include <iostream>


int Inventory::GetItemIndex(ItemType type) {
	// warning if an item isn't stackable it wil return first instance of that type
	for (auto &it : items)
	{
		if (it.second->GetType() == type)
			return it.first;
	}
	return -1;
}
int Inventory::GetItemIndex(Item& item) {
	if (!item.IsStackable()) return -1;
	return GetItemIndex(item.GetType());
}

void Inventory::AddItem(Item &item) {
	int existingIndex = GetItemIndex(item);
	if (item.IsStackable() && existingIndex != -1) {
		++itemQuantities[existingIndex];
	}
	else {
		int newIndex = GenerateIndex();
		items[newIndex] = &item; // TODO use pointer instead
		itemQuantities[newIndex] = 1;
	}
}

Item* Inventory::GetItem(int index) {
	if (items.count(index) == 1) {
		return items[index];
	}
	return nullptr;
};
int Inventory::GetItemQuantity(int index) {
	if (itemQuantities.count(index) == 1) {
		return itemQuantities[index];
	}
	return 0;
};

void Inventory::RemoveItem(int index) {
	if (itemQuantities.count(index) == 1) {
		--itemQuantities[index];
		if (itemQuantities[index] <= 0) {
			itemQuantities.erase(index);
			items.erase(index);
		}
	}
}
void Inventory::RemoveItem(ItemType type) {
	int index = GetItemIndex(type);
	if (index != -1) {
		RemoveItem(index);
	}
}

int Inventory::GenerateIndex() {
	return ++_currentIndex;
};

void Inventory::PrintContents() {
	for (auto& it : items)
	{
		int quantity = GetItemQuantity(it.first);
		std::cout << "Index " << it.first << " contains " << quantity << " " << it.second->GetLabel() << "s" << std::endl;
	}
	std::cout << std::endl;
}
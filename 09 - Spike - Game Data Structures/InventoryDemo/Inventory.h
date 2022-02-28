#pragma once

#include <map>
#include <vector>
#include <string>

#include "Item.h"

class Inventory {
public:
	int GetItemIndex(ItemType type);
	int GetItemIndex(Item &item);
	Item* GetItem(int index);
	int GetItemQuantity(int index);
	void AddItem(Item &item);
	void RemoveItem(int index);
	void RemoveItem(ItemType type);
	void PrintContents();
private:
	int GenerateIndex();

	std::map<int, int> itemQuantities;
	std::map<int, Item*> items;
	int _currentIndex = 0;
};
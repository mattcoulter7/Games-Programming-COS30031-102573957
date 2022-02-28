#pragma once

#include <map>
#include <vector>
#include <string>

#include "Item.h"

class Inventory {
public:
	int GetItemIndex(std::string name);
	int GetItemIndex(Item& item);
	Item* GetItem(std::string type);
	Item* GetItem(int index);
	int GetItemQuantity(std::string type);
	int GetItemQuantity(int index);
	void AddItem(Item &item);
	void RemoveItem(std::string name);
	void PrintContents();
	void RemoveItem(int index);

	std::map<int, Item*> GetItems();
private:
	int GenerateIndex();

	std::map<int, int> itemQuantities;
	std::map<int, Item*> items;
	int _currentIndex = 0;
};
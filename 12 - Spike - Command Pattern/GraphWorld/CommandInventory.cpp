#include "CommandInventory.h"

std::string CommandInventory::Process(std::vector<std::string> input) {
	std::string result = "";

	Inventory* inv = world->GetPlayer()->GetInventory();
	std::map<int, Item*> items = inv->GetItems();
	if (items.size() == 0)
		result += "No items in the inventory.\n";
	for (auto& it : items)
	{
		int quantity = inv->GetItemQuantity(it.first);
		result += " *" + std::to_string(quantity) + " " + it.second->GetLabel() + "s" + "\n";
	}
	return result;
};
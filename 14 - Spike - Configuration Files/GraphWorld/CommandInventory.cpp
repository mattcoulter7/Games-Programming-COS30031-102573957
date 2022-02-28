#include "CommandInventory.h"

std::string CommandInventory::Process(std::vector<std::string> input) {
	std::string result = "";

	Inventory* inv = world->GetPlayer()->GetInventory();
	std::vector<Entity*> items = inv->GetItems();
	if (items.size() == 0)
		result += "No items in the inventory.\n";
	for (Entity* it : items)
	{
		std::string label = it->GetLabel();
		result += " *" + label;
	}
	return result;
};
#include "CommandLook.h"

std::string CommandLook::Process(std::vector<std::string> input) {
	std::string result = "";

	Location* location = world->GetLocation();
	Inventory* inventory = location->GetInventory();

	if (input.size() == 1 || input.size() == 2) {
		result += "What are you looking at?\n";
	}
	else {
		Item* item = inventory->GetItem(input[2]);
		if (item == nullptr) {
			result += input[2] + " does not exist in " + location->GetName();
		}
		else {
			result += "You are looking at " + item->GetLabel();
		}
	}

	return result;
};
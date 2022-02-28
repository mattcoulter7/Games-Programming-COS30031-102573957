#include "CommandDrop.h"

std::string CommandDrop::Process(std::vector<std::string> input) {
	std::string result = "";

	Inventory* playerInv = world->GetPlayer()->GetInventory();
	Inventory* worldInv = world->GetLocation()->GetInventory();

	if (input.size() == 1) {
		result += "What are you trying to pickup?";
	}
	else {
		std::string itemName = input[1];
		Entity* item = playerInv->GetItem(itemName);
		if (item == nullptr) {
			result += "You do not have a " + itemName + " to drop";
		}
		else {
			if (item->HasComponent(ComponentType::Dropable)) {
				worldInv->AddItem(item);
				playerInv->RemoveItem(item);
				result += "Dropped 1 " + item->GetLabel();
			}
			else {
				result += "The " + item->GetLabel() + " cannot be dropped.";
			}
		}
	}

	return result;
};
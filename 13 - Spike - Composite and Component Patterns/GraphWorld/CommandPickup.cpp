#include "CommandPickup.h"

std::string CommandPickup::Process(std::vector<std::string> input) {
	std::string result = "";

	Inventory* playerInv = world->GetPlayer()->GetInventory();
	Inventory* worldInv = world->GetLocation()->GetInventory();

	if (input.size() == 1) {
		result += "What are you trying to pickup?";
	}
	else {
		std::string itemName = input[1];
		Entity* worldItem = worldInv->GetItem(itemName);
		if (worldItem == nullptr) {
			result += world->GetLocation()->GetName() + " does not have item " + itemName;
		}
		else {
			if (worldItem->HasComponent(ComponentType::Pickupable)) {
				worldInv->RemoveItem(worldItem);
				playerInv->AddItem(worldItem);
				result += "Picked up 1 " + worldItem->GetLabel();
			}
			else {
				result += "The " + worldItem->GetLabel() + " cannot be picked up.";
			}
		}
	}

	return result;
};
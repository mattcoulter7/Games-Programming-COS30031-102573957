#include "CommandOpen.h"

#include "ComponentOpenable.h"
#include "ComponentLocked.h"

std::string CommandOpen::Process(std::vector<std::string> input) {
	std::string result = "";

	Inventory* playerInv = world->GetPlayer()->GetInventory();
	Inventory* worldInv = world->GetLocation()->GetInventory();

	if (input.size() == 1) {
		result += "What are you trying to open?";
    }
    else {
        std::string itemName = input[1]; // what they are trying to open

        Location* location = world->GetLocation();
		Entity* worldItem = worldInv->GetItem(itemName);

		if (worldItem == nullptr) {
			result += world->GetLocation()->GetName() + " does not have item " + itemName;
		}
		else {
			ComponentOpenable* openable = static_cast<ComponentOpenable*>(worldItem->GetComponent(ComponentType::Openable));
			if (openable != nullptr) {
				if (openable->state == OpenState::Opened) {
					result += "You have already opened the " + worldItem->GetLabel() + "\n";
				}
				else if (openable->state == OpenState::Closed) {
					ComponentLocked* lock = static_cast<ComponentLocked*>(worldItem->GetComponent(ComponentType::Locked));
					if (lock == nullptr || lock->state == LockedState::Unlocked) {
						openable->state = OpenState::Opened;
						// open the chest
						result += "You have opened the " + worldItem->GetLabel() + "\n";

						std::vector<Entity*> children = worldItem->GetChildren();
						int numChildren = children.size();
						if (numChildren == 0) {
							result += "There isn't anything inside";
						}
						else {
							result += "Inside contains:\n";
							result += worldItem->GetContents();
						}

						// move all the items into the world inventory so they can be interacted with
						for (Entity* e : children) {
							worldInv->AddItem(e);
						}
					}
					else {
						// check if the chest is locked
						if (lock->state == LockedState::Locked) {
							result += "The " + worldItem->GetLabel() + " is locked, try unlocking it!";
						}
					}
				}
			}
			else {
				result += "The " + worldItem->GetLabel() + " cannot be opened.";
			}
		}
        return result;
    }
};
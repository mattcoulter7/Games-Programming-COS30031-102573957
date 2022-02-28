#include "CommandLook.h"

#include "ComponentOpenable.h"
#include "ComponentLocked.h"

std::string CommandLook::Process(std::vector<std::string> input) {
	std::string result = "";

	Location* location = world->GetLocation();
	Inventory* inventory = location->GetInventory();

	if (input.size() == 1 || input.size() == 2) {
		result += "What are you looking at?\n";
	}
	else {
		Entity* item = inventory->GetItem(input[2]);

		ComponentOpenable* openable = static_cast<ComponentOpenable*>(item->GetComponent(ComponentType::Openable));
		ComponentLocked* lock = static_cast<ComponentLocked*>(item->GetComponent(ComponentType::Locked));

		if (item == nullptr) {
			result += input[2] + " does not exist in " + location->GetName();
		}
		else {
			if (openable == nullptr || openable->state == OpenState::Opened) {
				result += "You are looking at " + item->GetDescription() + "\n";
				result += "Inside Contains:\n";
				result += item->GetContents();
			}
			else {
				if (openable->state == OpenState::Closed) {
					result += "Looks like the " + item->GetLabel() + " is not open.\n";
					if (lock != nullptr && lock->state == LockedState::Locked) {
						result += "The " + item->GetLabel() + " is locked, perhaps there is a key somehwhere to open it";
					}
				}
			}
		}
	}

	return result;
};
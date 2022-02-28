#include "CommandUnlock.h"

#include "ComponentLocked.h"
#include "ComponentUnlock.h"

std::string CommandUnlock::Process(std::vector<std::string> input) {
	std::string result = "";

	Inventory* playerInv = world->GetPlayer()->GetInventory();
	Inventory* worldInv = world->GetLocation()->GetInventory();

	if (input.size() == 1) {
		result += "What are you trying to unlock?";
	}
	else {
		std::string itemName = input[1]; // what they are trying to unlock

		Location* location = world->GetLocation();
		Entity* worldItem = worldInv->GetItem(itemName);

		if (worldItem == nullptr) {
			result += world->GetLocation()->GetName() + " does not have item " + itemName;
		}
		else {
			ComponentLocked* lock = static_cast<ComponentLocked*>(worldItem->GetComponent(ComponentType::Locked));
			if (lock != nullptr) {
				if (lock->state == LockedState::Unlocked) {
					// open the chest
					result += "The " + worldItem->GetLabel() + " is already unlocked!";
				}
				else if (lock->state == LockedState::Locked) {
					// check if the chest is locked
					Entity* key = playerInv->GetItem(EntityType::Key);
					if (key == nullptr) {
						result += "You don't have a key to unlock the " + worldItem->GetLabel();
					}
					else {
						ComponentUnlock* keyUnlock = static_cast<ComponentUnlock*>(key->GetComponent(ComponentType::Unlock));
						if (keyUnlock == nullptr) {
							result += "This key seems broken, I don't think it can unlock anything!";
						}
						else {
							if (keyUnlock->key == lock->key) { // keys match can perform unlock
								result += "I have unlocked the " + worldItem->GetLabel() + ", lets open it!";
								lock->state = LockedState::Unlocked;
							}
							else {
								result += "This key doesn't seem to fit the lock :(";
							}
						}
					}
				}
			}
			else {
				result += "The " + worldItem->GetLabel() + " doesn't have a lock!";
			}
		}
		return result;
	}
};
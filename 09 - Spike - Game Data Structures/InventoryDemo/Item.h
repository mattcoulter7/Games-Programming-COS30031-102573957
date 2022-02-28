#pragma once

#include <string>
#include "ItemEnum.h"

class Item {
public:
	Item(ItemType id, std::string label, bool stackable);
	ItemType GetType();
	std::string GetLabel();
	bool IsStackable();
private:
	ItemType _type;
	std::string _label;
	bool _stackable;
};
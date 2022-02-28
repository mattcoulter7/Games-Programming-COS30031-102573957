#include "Item.h"

Item::Item(ItemType id, std::string label, bool stackable) {
	_type = id;
	_label = label;
	_stackable = stackable;
};
ItemType Item::GetType() {
	return _type;
};
std::string Item::GetLabel() {
	return _label;
};
bool Item::IsStackable() {
	return _stackable;
};
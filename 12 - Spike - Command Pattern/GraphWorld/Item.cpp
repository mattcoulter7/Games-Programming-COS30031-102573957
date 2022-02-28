#include "Item.h"

Item::Item(std::string label, bool stackable) {
	_label = label;
	_stackable = stackable;
};
std::string Item::GetLabel() {
	return _label;
};
bool Item::IsStackable() {
	return _stackable;
};
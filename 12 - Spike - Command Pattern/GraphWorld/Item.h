#pragma once

#include <string>

class Item {
public:
	Item(std::string label, bool stackable);
	std::string GetLabel();
	bool IsStackable();
private:
	std::string _label;
	bool _stackable;
};
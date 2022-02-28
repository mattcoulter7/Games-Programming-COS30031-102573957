#pragma once

#include <string>
#include <map>

#include "json.hpp"
using json = nlohmann::json;

#include "Inventory.h"

class Location {
public:
	Location(json _json);

	int GetId();
	std::string GetName();
	std::string GetDescription();
	std::map<std::string, int> GetDirections();
	Inventory* GetInventory();

private:
	int id;
	std::string name;
	std::string description;
	std::map<std::string, int> directions;
	Inventory* inventory;
};
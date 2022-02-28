#pragma once

#include <string>
#include <map>

#include "json.hpp"
using json = nlohmann::json;

#include "Inventory.h"

class Location {
public:
	Location(int _id,std::string _name,std::string _description,std::map<std::string, int> _directions);

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
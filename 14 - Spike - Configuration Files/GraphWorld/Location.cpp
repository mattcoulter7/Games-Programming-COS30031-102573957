#include "Location.h"
#include "EntityFactory.h"
Location::Location(json _json) {
	id = _json["id"];
	name = _json["Name"];
	description = _json["Description"];
	directions = _json.at("Directions").get<std::map<std::string, int>>();
	inventory = new Inventory();
	json JSONentities = _json["Entities"];
	for (auto entity : JSONentities) {
		inventory->AddItem(EntityFactory::Instance()->CreateEntity(entity));
	}
}

int Location::GetId() { return id; }
std::string Location::GetName() { return name; };
std::string Location::GetDescription() { return description; };
std::map<std::string, int> Location::GetDirections() { return directions; };
Inventory* Location::GetInventory() {
	return inventory;
};
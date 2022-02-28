#include "Location.h"

Location::Location(
	int _id,
	std::string _name,
	std::string _description,
	std::map<std::string, int> _directions
) {
	id = _id;
	name = _name;
	description = _description;
	directions = _directions;
};

Location::Location(json _json) {
	id = _json["id"];
	name = _json["Name"];
	description = _json["Description"];
	directions = _json.at("Directions").get<std::map<std::string, int>>();
}

int Location::GetId() { return id; }
std::string Location::GetName() { return name; };
std::string Location::GetDescription() { return description; };
std::map<std::string, int> Location::GetDirections() { return directions; };
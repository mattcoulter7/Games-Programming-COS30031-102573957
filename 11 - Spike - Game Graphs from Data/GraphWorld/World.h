#pragma once

#include <vector>

#include "Location.h"

#include "json.hpp"
using json = nlohmann::json;

class World {
public:
	World(
		int _id, 
		std::string _name,
		std::string _description,
		int _startLocation,
		std::vector<Location> _locations
	);
	World(json _json);
	void Play();
	bool IsRunning();
	void AddLocation(Location location);
	Location* GetLocation();
	Location* GetLocation(int id);
	int GetId();
private:
	void SetLocation(int id);


	int id;
	std::string name;
	std::string description;

	int startLocation;
	int currentLocation;
	std::vector<Location> locations;
	bool running;
};
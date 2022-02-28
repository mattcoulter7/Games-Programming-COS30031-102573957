#pragma once

#include <vector>
#include "Player.h"
#include "Location.h"
#include "json.hpp"
using json = nlohmann::json;

class CommandManager;

class World {
public:
	World(json _json);
	void Play();
	void End();
	bool IsRunning();
	void AddLocation(Location location);
	Location* GetLocation();
	Location* GetLocation(int id);
	void SetLocation(int id);
	int GetId();
	std::string GetName();
	std::string GetDescription();
	Player* GetPlayer();

	static std::string dir_check(std::string key);
	static std::map<std::string, std::string> dir_alias;

private:
	Player* player;
	int id;
	std::string name;
	std::string description;
	CommandManager* commandManager;
	int startLocation;
	std::vector<Location> locations;
	bool running;
};
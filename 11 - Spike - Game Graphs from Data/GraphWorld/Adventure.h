#pragma once

#include "World.h"


#include <vector>
#include <string>

#include "json.hpp"
using json = nlohmann::json;

class Adventure {
public:
	bool LoadFile(std::string dir);
	void LoadFile();
	World* GetWorld(int id);
	void AddWorld(World world);

	void PlayWorld(int id);
private:
	int currentWorld;
	std::vector<World> worlds;
};
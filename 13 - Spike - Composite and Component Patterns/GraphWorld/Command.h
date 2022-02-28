#pragma once

#include <string>
#include <vector>

#include "World.h"

class Command {
public:
	Command(World* _world) {
		world = _world;
	};
	virtual std::string Process(std::vector<std::string> input) = 0;
protected:
	World* world;
};
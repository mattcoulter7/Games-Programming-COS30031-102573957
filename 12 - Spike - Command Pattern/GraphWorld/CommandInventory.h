#pragma once

#include "Command.h"

class CommandInventory : public Command {
public:
	CommandInventory(World* _world) : Command(_world) {};
	std::string Process(std::vector<std::string> input) override;
};
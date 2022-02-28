#pragma once

#include "Command.h"

class CommandOpen : public Command {
public:
	CommandOpen(World* _world) : Command(_world) {};
	std::string Process(std::vector<std::string> input) override;
};
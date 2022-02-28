#pragma once

#include "Command.h"

class CommandDebugTree : public Command {
public:
	CommandDebugTree(World* _world) : Command(_world) {};
	std::string Process(std::vector<std::string> input) override;
};
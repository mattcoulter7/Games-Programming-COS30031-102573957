#pragma once

#include "Command.h"

class CommandQuit : public Command {
public:
	CommandQuit(World* _world) : Command(_world) {};
	std::string Process(std::vector<std::string> input) override;
};
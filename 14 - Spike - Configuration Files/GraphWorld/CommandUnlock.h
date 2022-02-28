#pragma once

#include "Command.h"

class CommandUnlock : public Command {
public:
	CommandUnlock(World* _world) : Command(_world) {};
	std::string Process(std::vector<std::string> input) override;
};
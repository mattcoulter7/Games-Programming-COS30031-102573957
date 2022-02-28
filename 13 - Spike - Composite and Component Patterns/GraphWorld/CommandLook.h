#pragma once

#include "Command.h"

class CommandLook : public Command {
public:
	CommandLook(World* _world) : Command(_world) {};
	std::string Process(std::vector<std::string> input) override;
};
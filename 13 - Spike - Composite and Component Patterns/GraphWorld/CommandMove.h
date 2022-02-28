#pragma once

#include "Command.h"

class CommandMove : public Command{
public:
	CommandMove(World* _world) : Command(_world) {};
	std::string Process(std::vector<std::string> input) override;
};
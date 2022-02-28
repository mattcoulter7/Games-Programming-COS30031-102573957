#pragma once

#include "Command.h"

class CommandHelp : public Command {
public:
	CommandHelp(World* _world, CommandManager* _commandManager) : Command(_world) {
		commandManager = _commandManager;
	};
	std::string Process(std::vector<std::string> input) override;
private:
	CommandManager* commandManager;
};
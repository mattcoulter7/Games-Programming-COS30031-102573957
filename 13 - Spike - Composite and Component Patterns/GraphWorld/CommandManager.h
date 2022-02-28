#pragma once

#include <map>

#include "Command.h"
#include "CommandMove.h"
#include "CommandDebugTree.h"
#include "CommandHelp.h"
#include "CommandInventory.h"
#include "CommandLook.h"
#include "CommandQuit.h"
#include "CommandPickup.h"
#include "CommandDrop.h"

class CommandManager {
public:
	CommandManager(World* _world);
	std::string Process(std::string input);
	std::map<std::string, Command*> GetCmds();
private:
	std::map<std::string, Command*> cmds;
	World* world;
};
#include "CommandHelp.h"
#include "CommandManager.h"

std::string CommandHelp::Process(std::vector<std::string> input) {
	std::string result = "";

	std::map<Command*,std::string> cmdsGrouped = {};
	std::map<std::string, Command*> cmds = commandManager->GetCmds();
	for (const auto& it : cmds) {
		if (cmdsGrouped.count(it.second))
			cmdsGrouped[it.second] += ", " + it.first;
		else
			cmdsGrouped[it.second] = it.first;
	}

	for (const auto& it : cmdsGrouped) {
		result += " *" + it.second + "\n";
	}

	return result;
};
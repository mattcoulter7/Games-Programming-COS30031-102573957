#include "CommandManager.h"

//#region placing these here because not using console system yet..
typedef std::vector<std::string> split;
split SplitString(std::string str, char delim = ' ') {
	split words;
	std::string currentWord = "";
	for (int i = 0; i < str.size(); i++) {
		char currentLetter = str[i];
		if (currentLetter == delim) {
			words.push_back(currentWord);
			currentWord = "";
		}
		else {
			currentWord.push_back(currentLetter);
		}
	}
	words.push_back(currentWord);
	return words;
}

void toLowerCase(std::string& value) {
	for (std::string::size_type i = 0; i < value.size(); ++i) {
		value[i] = tolower(value[i]);
	}
};
//#endregion

CommandManager::CommandManager(World* _world) {
	world = _world;

    cmds.emplace("move",new CommandMove(_world));
	cmds.emplace("go", cmds["move"]); // alias to move

	cmds.emplace("debugtree", new CommandDebugTree(_world));
	cmds.emplace("debug", cmds["debugtree"]); // alias to move

	cmds.emplace("help", new CommandHelp(_world,this));

	cmds.emplace("inventory", new CommandInventory(_world)); 

	cmds.emplace("look", new CommandLook(_world));

	cmds.emplace("quit", new CommandQuit(_world));
	cmds.emplace("q", new CommandQuit(_world));

	cmds.emplace("pickup", new CommandPickup(_world));
	cmds.emplace("take", cmds["pickup"]); // alias to pickup

	cmds.emplace("drop", new CommandDrop(_world));
}

std::string CommandManager::Process(std::string input) {
	toLowerCase(input);
	split splitInput = SplitString(input);
	if (splitInput.size() == 0) return "";
	std::string keyword = splitInput[0];
	if (cmds.count(keyword)) {
		Command* command = cmds[keyword];
		return command->Process(splitInput);
	}
	return "Invalid Command";
}

std::map<std::string, Command*> CommandManager::GetCmds() { return cmds; };
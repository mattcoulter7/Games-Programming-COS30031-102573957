#include "CommandDebugTree.h"

std::string CommandDebugTree::Process(std::vector<std::string> input) {
	std::string result = "";
	result += "World Id: " + std::to_string(world->GetId());
	result += "\nWorld Name: " + world->GetName();
	result += "\nWorld Description: " + world->GetDescription();

	Location* location = world->GetLocation();
	result += "\n\nLocation Id: " + std::to_string(location->GetId());
	result += "\nLocation Name: " + location->GetName();
	result += "\nLocation Description: " + location->GetDescription();


	return result;
};
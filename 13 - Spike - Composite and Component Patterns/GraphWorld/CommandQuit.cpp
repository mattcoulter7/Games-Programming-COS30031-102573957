#include "CommandQuit.h"

std::string CommandQuit::Process(std::vector<std::string> input) {
	world->End();
	return "";
};
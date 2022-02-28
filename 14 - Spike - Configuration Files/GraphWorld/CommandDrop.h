#include "Command.h"

class CommandDrop : public Command {
public:
	CommandDrop(World* _world) : Command(_world) {};
	std::string Process(std::vector<std::string> input) override;
};
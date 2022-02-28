#include "Command.h"

class CommandPickup : public Command {
public:
	CommandPickup(World* _world) : Command(_world) {};
	std::string Process(std::vector<std::string> input) override;
};
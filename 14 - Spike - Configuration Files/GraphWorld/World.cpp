#include "World.h"
#include "iostream"

#include "CommandManager.h"

World::World(json _json) {
	id = _json["id"];
	name = _json["Name"];
	description = _json["Description"];
	startLocation = _json["StartLocation"];
	for (json location : _json.at("Locations"))
		AddLocation(Location(location));
	commandManager = new CommandManager(this);
	player = new Player();
}
void World::End() {
	running = false;
}
void World::Play() {
	running = true;

	std::cout << name << std::endl;
	std::cout << description << std::endl;
	std::cout << "-----------------------------------------------------------------------------------" << std::endl;
	player->SetLocation(startLocation);

	while (running) {
		std::map<std::string, int> dirs = GetLocation()->GetDirections();

		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);
		std::cout << commandManager->Process(input) << std::endl;
	}

	std::cout << "-----------------------------------------------------------------------------------" << std::endl;
	std::cout << "Thanks for playing." << std::endl;
}

Location* World::GetLocation() {return GetLocation(player->GetLocation());}
Location* World::GetLocation(int id) {
	for (auto &loc : locations) {
		if (loc.GetId() == id)
			return &loc;
	}
	return nullptr;
}

bool World::IsRunning() {
	return running;
}
void World::AddLocation(Location location) {
	locations.push_back(location);
}

int World::GetId() { return id; }
std::string World::GetName() { return name; };
std::string World::GetDescription() { return description; };
Player* World::GetPlayer() { return player; };
void World::SetLocation(int id) {
	Location* loc = GetLocation(id);
	if (loc == nullptr) {
		std::cout << "How did you get here?" << std::endl;
		return;
	}

	std::cout << "You have arrived at " << loc->GetName() << std::endl;
	std::cout << loc->GetDescription() << std::endl;

	player->SetLocation(id);
};

// Static Members
std::map<std::string, std::string> World::dir_alias{ 
	{ "n", "north" },
	{ "e", "east" },
	{ "s", "south" },
	{ "w", "west" },
	{ "ne", "northeast" },
	{ "se", "southeast" },
	{ "sw", "southwest" },
	{ "nw", "northwest" },
	{ "u", "up" },
	{ "d", "down" }
}; 
std::string World::dir_check(std::string key) {
	if (dir_alias.count(key)) {
		return dir_alias[key];
	}
	return key;
}
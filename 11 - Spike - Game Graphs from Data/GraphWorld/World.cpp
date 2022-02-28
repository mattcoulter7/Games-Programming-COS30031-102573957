#include "World.h"
#include "iostream"

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

World::World(
	int _id, std::string _name, 
	std::string _description,
	int _startLocation,
	std::vector<Location> _locations
) {
	id = _id;
	name = _name;
	description = _description;
	startLocation = _startLocation;
	locations = _locations;
}

World::World(json _json) {
	id = _json["id"];
	name = _json["Name"];
	description = _json["Description"];
	startLocation = _json["StartLocation"];
	for (json location : _json.at("Locations"))
		AddLocation(Location(location));
}
void World::Play() {
	running = true;

	std::cout << name << std::endl;
	std::cout << description << std::endl;
	std::cout << "-----------------------------------------------------------------------------------" << std::endl;
	SetLocation(startLocation);

	while (running) {
		std::map<std::string, int> dirs = GetLocation()->GetDirections();

		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);
		toLowerCase(input);
		split splitInput = SplitString(input);
		if (splitInput[0] == "go") {
			std::string direction = splitInput[1];
			int result = dirs.count(direction) ? dirs[direction] : -1;
			if (result != -1) {
				SetLocation(result);
			}
			else {
				std::cout << "Can't move " << direction << std::endl;
			}
		}
		else if (splitInput[0] == "quit") {
			running = false;
		}
		else
		{
			std::cout << "Invalid Command" << std::endl;
		}
	}

	std::cout << "-----------------------------------------------------------------------------------" << std::endl;
	std::cout << "Thanks for playing." << std::endl;
}

Location* World::GetLocation() {return GetLocation(currentLocation);}
Location* World::GetLocation(int id) {
	for (auto& loc : locations) {
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
void World::SetLocation(int id) {
	Location* loc = GetLocation(id);
	if (loc == nullptr) {
		std::cout << "How did you get here?" << std::endl;
		return;
	}

	std::cout << "You have arrived at " << loc->GetName() << std::endl;
	std::cout << loc->GetDescription() << std::endl;

	currentLocation = id;
};
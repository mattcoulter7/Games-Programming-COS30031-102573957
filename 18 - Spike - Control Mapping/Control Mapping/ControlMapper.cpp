#include "ControlMapper.h"

#include <fstream>

ControlMapper::ControlMapper(std::string path) {
	_path = path;
	Load();
};
ControlMapper::~ControlMapper() {};
void ControlMapper::Load() {
	try {
		// a.Open the file(text mode, read only),
		std::ifstream infile;
		infile.open(_path, std::ios::in);

		// b.load content into file
		std::string content((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));

		// c. parse the json string into the json object
		auto jObject = json::parse(content);

		// d. print the output
		for (auto it = jObject.begin(); it != jObject.end(); ++it) {
			Actions action = static_cast<Actions>(atoi(it.key().c_str()));
			Uint8 bind = static_cast<Uint8>(it.value());
			SetControl(action, bind);
		}
	}
	catch (const std::exception&) {}
};
void ControlMapper::Save() {
	json jsonfile;
	for (auto& pair : _controlMap) {
		std::string action = std::to_string(static_cast<Uint8>(pair.first));
		Uint8 bind = pair.second;
		jsonfile[action] = pair.second;
	}
	std::ofstream file(_path);
	file << jsonfile;
};
// get all of th inputs that match a certain control
Uint8 ControlMapper::GetControlInput(Actions control) {
	return _controlMap[control];
};
// return all of the controls that match a certain input
std::vector<Actions> ControlMapper::GetControls(Uint8 key) {
	std::vector<Actions> controls;
	for (auto& pair : _controlMap) {
		if (key == pair.second) {
			controls.push_back(pair.first);
		}
	}
	return controls;
}
// set a control mapping
void ControlMapper::SetControl(Actions control, Uint8 input) {
	_controlMap[control] = input;
	Save();
};

ControlMapper& ControlMapper::Instance() {
	return m_instance;
}
ControlMapper ControlMapper::m_instance = ControlMapper("bindings.json");


std::array<std::string, 6> ControlMapper::ControlsArray = {
	"MOVEUP",
	"MOVERIGHT",
	"MOVEDOWN",
	"MOVELEFT",
	"SHOOT",
	"RETURNTOMAINMENU"
};

Uint8 ControlMapper::GetInputCode(SDL_Event& event) {
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		return event.button.button;
	case SDL_KEYDOWN:
		return event.key.keysym.sym;
	default:
		return -1;
	}
	return -1;
};
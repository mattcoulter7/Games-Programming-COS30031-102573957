#pragma once

#include <map>
#include <vector>
#include <array>
#include <string>
#include "SDL.h"

#include "json.hpp"
using json = nlohmann::json;

enum class Actions {
	MOVEUP,
	MOVERIGHT,
	MOVEDOWN,
	MOVELEFT,
	SHOOT,
	RETURNTOMAINMENU
};
typedef std::map<Actions, Uint8> ControlMap;
class ControlMapper {
public:
	ControlMapper(std::string path);
	~ControlMapper();

	Uint8 GetControlInput(Actions control);// get all of th inputs that match a certain control
	std::vector<Actions> GetControls(Uint8 key);// return all of the controls that match a certain input
	void SetControl(Actions control, Uint8 input);// set a control mapping
	void Load();// load the control map from a file
	void Save();// save the control map to a file
	
	static ControlMapper& Instance();// singleton
	static Uint8 GetInputCode(SDL_Event& event);
	static std::array<std::string, 6> ControlsArray;
private:
	static ControlMapper m_instance;
	ControlMap _controlMap;
	std::string _path;
};
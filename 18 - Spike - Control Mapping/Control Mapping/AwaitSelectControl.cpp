#include "AwaitSelectControl.h"

#include "AwaitKeyBind.h"
#include "StateManager.h"
#include "ControlMapper.h"
#include "MainMenu.h"

void AwaitSelectControl::Update(StateManager& configurer, SDL_Event& event) {
	// if the enter a number to reassign a key, enter the enter keybind mode
	Uint8 key = ControlMapper::GetInputCode(event);
	if (key == SDLK_ESCAPE) {
		configurer.SetState(new MainMenu());
		return;
	}
	int index;
	try {
		index = std::stoi(SDL_GetKeyName(key)) - 1; // throws error if fail to convert
	}
	catch (const std::exception&) {
		return;
	}
	if (index > ControlMapper::ControlsArray.size()) return;

	Actions controlToBind = static_cast<Actions>(index);
	configurer.SetState(new AwaitKeyBind(controlToBind));
};
void AwaitSelectControl::Render() {
	system("cls");
	// render what the current control layout is
	ControlMapper& cm = ControlMapper::Instance();
	for (size_t i = 0; i < ControlMapper::ControlsArray.size(); i++) {
		std::string identifier = ControlMapper::ControlsArray[i];
		Actions control = static_cast<Actions>(i);
		Uint8 assigned = cm.GetControlInput(control);
		std::string keyName = SDL_GetKeyName(assigned);

		std::cout << i + 1 << ". " << identifier << " [" << keyName << "]" << std::endl;
	}
};
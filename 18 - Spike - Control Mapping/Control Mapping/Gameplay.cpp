#include "Gameplay.h"

#include "StateManager.h"
#include "ControlMapper.h"
#include "MainMenu.h"

void Gameplay::Update(StateManager& configurer, SDL_Event& event) {
	Uint8 key = ControlMapper::GetInputCode(event);
	std::vector<Actions> actions = ControlMapper::Instance().GetControls(key);
	for (Actions& action : actions) {
		if (action == Actions::RETURNTOMAINMENU) {
			configurer.SetState(new MainMenu());
		}

		size_t index = static_cast<size_t>(action);
		std::string identifier = ControlMapper::ControlsArray[index];
		std::cout << identifier << std::endl;
	}
};
void Gameplay::Render() {};
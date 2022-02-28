#include "MainMenu.h"

#include "StateManager.h"
#include "ControlMapper.h"
#include "Gameplay.h"
#include "AwaitSelectControl.h"

void MainMenu::Update(StateManager& configurer, SDL_Event& event) {
	Uint8 key = ControlMapper::GetInputCode(event);
	if (key == SDLK_1) {
		configurer.SetState(new Gameplay());
	}
	else if (key == SDLK_2) {
		configurer.SetState(new AwaitSelectControl());
	}
};
void MainMenu::Render() {
	system("cls");
	std::cout << "1. Test Controls" << std::endl;
	std::cout << "2. Change Controls" << std::endl;
};
#pragma once

#include "BaseMenuState.h"

class ControlMapper;
class MainMenu : public BaseState {
	void Update(StateManager& configurer, SDL_Event& event);
	void Render();
};
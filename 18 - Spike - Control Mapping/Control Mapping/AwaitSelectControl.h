#pragma once

#include "BaseMenuState.h"

class AwaitKeyBind;
class ControlMapper;
class AwaitSelectControl : public BaseState {
	void Update(StateManager& configurer, SDL_Event& event);
	void Render();
};
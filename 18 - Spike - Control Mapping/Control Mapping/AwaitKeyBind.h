#pragma once

#include "BaseMenuState.h"

class AwaitSelectControl;
class ControlMapper;
enum class Actions;
class AwaitKeyBind : public BaseState {
public:
	AwaitKeyBind(Actions bindKey);
	void Update(StateManager& configurer, SDL_Event& event);
	void Render();
private:
	Actions _bindKey;
};
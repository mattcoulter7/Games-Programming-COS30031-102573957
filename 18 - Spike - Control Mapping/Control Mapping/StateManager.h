#pragma once

#include "SDL.h"

class BaseState;
class StateManager {
public:
	StateManager();
	~StateManager();
	void SetState(BaseState* state);
	BaseState* GetState();
	void Update(SDL_Event& event);
	void Render();
private:
	BaseState* _state;
};
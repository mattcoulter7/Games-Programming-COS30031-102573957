#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cmath>

#include "SDL.h"

class StateManager;
class BaseState {
public:
	BaseState() {};
	~BaseState() {};
	virtual void Update(StateManager& configurer, SDL_Event& event) = 0;
	virtual void Render() = 0;
};
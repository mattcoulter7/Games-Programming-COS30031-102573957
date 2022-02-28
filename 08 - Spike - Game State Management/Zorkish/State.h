#pragma once

#include "Console.h"

#include "StateManager.h"

class State {
public:
	virtual std::string GetInput() = 0;
	virtual void Update(StateManager *stateManager, std::string input) = 0;
	virtual void Render() = 0;
};
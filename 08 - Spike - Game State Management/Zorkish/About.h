#pragma once

#include "State.h"

class About : public State {
public:
    std::string GetInput();
    void Update(StateManager* stateManager, std::string input);
    void Render();

	static About* Instance() {
		return &m_AboutState;
	};
private:
	static About m_AboutState;
};
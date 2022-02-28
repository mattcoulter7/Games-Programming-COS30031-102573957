#pragma once

#include "State.h"

class Help : public State {
public:
    std::string GetInput();
    void Update(StateManager* stateManager, std::string input);
    void Render();

	static Help* Instance() {
		return &m_HelpState;
	};
private:
	static Help m_HelpState;
};
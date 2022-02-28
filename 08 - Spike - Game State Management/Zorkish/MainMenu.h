#pragma once

#include "State.h"

class MainMenu : public State {
public:
    std::string GetInput();
    void Update(StateManager* stateManager, std::string input);
    void Render();

	static MainMenu* Instance() {
		return &m_MainMenuState;
	};
private:
	static MainMenu m_MainMenuState;
};
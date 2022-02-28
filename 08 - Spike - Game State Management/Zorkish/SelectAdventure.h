#pragma once

#include "State.h"

class SelectAdventure : public State {
public:
    std::string GetInput();
    void Update(StateManager* stateManager, std::string input);
    void Render();

	static SelectAdventure* Instance() {
		return &m_SelectAdventureState;
	};
private:
	static SelectAdventure m_SelectAdventureState;
};
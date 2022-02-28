#pragma once

#include "State.h"

class NewHighScore : public State {
public:
    std::string GetInput();
    void Update(StateManager* stateManager, std::string input);
    void Render();

	static NewHighScore* Instance() {
		return &m_NewHighScoreState;
	};
private:
	static NewHighScore m_NewHighScoreState;
};
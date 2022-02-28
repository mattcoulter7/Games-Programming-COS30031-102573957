#pragma once

#include "State.h"

class HallOfFame : public State {
public:
    std::string GetInput();
    void Update(StateManager* stateManager, std::string input);
    void Render();

	static HallOfFame* Instance() {
		return &m_HallOfFameState;
	};
private:
	static HallOfFame m_HallOfFameState;
};
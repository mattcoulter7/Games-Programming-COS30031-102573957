#pragma once

#include "State.h"

class Gameplay : public State {
public:
	Gameplay();
    std::string GetInput();
    void Update(StateManager* stateManager, std::string input);
    void Render();

	int GetScore();
	int GetMoveCount();
	std::vector<std::string> GetValidCommands();
	std::map<std::string, std::string> GetMaps();
	std::string GetCurrentMap();
	void SetCurrentMap(std::string val);

	static Gameplay* Instance() {
		return &m_GameplayState;
	};

private:
	void LoadValidCommands();
	void LoadMaps();

	std::string _currentMap;
	std::vector<std::string> _validCommands;
	std::map<std::string, std::string> _maps;
	int _score;
	int _moveCount;

	static Gameplay m_GameplayState;
};


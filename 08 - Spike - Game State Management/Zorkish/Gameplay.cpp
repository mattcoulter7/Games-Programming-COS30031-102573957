#include "Gameplay.h"

#include "MainMenu.h"
#include "NewHighScore.h"

Gameplay Gameplay::m_GameplayState;
Gameplay::Gameplay() {
    LoadValidCommands();
    LoadMaps();
};
std::string Gameplay::GetInput() {
    return Console::AwaitValidatedInput(_validCommands, "");
};
void Gameplay::Update(StateManager* stateManager, std::string input) {
    if (input == "quit") {
        std::cout << "Your adventure has ended without fame or fortune." << std::endl;
        stateManager->SetState(MainMenu::Instance());
    }
    else if (input == "hiscore") {
        std::cout << "You have entered the magic word and will now see the \"New High Score\" screen." << std::endl;
        stateManager->SetState(NewHighScore::Instance());
    }
};
void Gameplay::Render() {
    system("cls");
    std::string map_name = _maps[_currentMap];
    std::cout << "Welcome to Zorkish: " << map_name << std::endl;
    std::cout << "This world is simple and pointless. Used it to test Zorkish phase 1 spec." << std::endl;
};
void Gameplay::LoadValidCommands() {
    // Commands should be defined in lowercase for case insensitivity
    _validCommands = {
        "quit",
        "hiscore"
    };
}
void Gameplay::LoadMaps() {
    _maps["1"] = "Mountain World";
    _maps["2"] = "Water World";
    _maps["3"] = "Box World";
}

// Getters/Setters
int Gameplay::GetScore() { return _score; }
int Gameplay::GetMoveCount() { return _moveCount; }
std::vector<std::string> Gameplay::GetValidCommands() { return _validCommands; }
std::map<std::string, std::string> Gameplay::GetMaps() { return _maps; }
std::string Gameplay::GetCurrentMap() { return _currentMap; }
void Gameplay::SetCurrentMap(std::string val) { _currentMap = val; }
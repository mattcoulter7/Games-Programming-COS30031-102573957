#include "NewHighScore.h"

#include "Gameplay.h"
#include "MainMenu.h"

NewHighScore NewHighScore::m_NewHighScoreState;
std::string NewHighScore::GetInput() {
    std::string input;
    std::cin >> input;
    return input;
};
void NewHighScore::Update(StateManager* stateManager, std::string input) {
    stateManager->SetState(MainMenu::Instance());
};
void NewHighScore::Render() {
    system("cls");
    std::cout << "Zorkish :: New High Score" << std::endl;
    Console::Line();
    std::cout << "Congratulations!" << std::endl << std::endl
        << "You have made it to the Zorkish Hall Of Fame" << std::endl << std::endl
        << "Adventure: " << Gameplay::Instance()->GetMaps()[Gameplay::Instance()->GetCurrentMap()] << std::endl
        << "Score: " << Gameplay::Instance()->GetScore() << std::endl
        << "Moves: " << Gameplay::Instance()->GetMoveCount() << std::endl << std::endl
        << "Please type your name and press enter" << std::endl;
};
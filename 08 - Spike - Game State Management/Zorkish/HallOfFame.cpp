#include "HallOfFame.h"

#include "MainMenu.h"

HallOfFame HallOfFame::m_HallOfFameState;
std::string HallOfFame::GetInput() {
    Console::AwaitEnter("Press Enter to return to the Main Menu");
    return "";
};
void HallOfFame::Update(StateManager* stateManager, std::string input) {
    stateManager->SetState(MainMenu::Instance());
};
void HallOfFame::Render() {
    system("cls"); // clear the console
    std::cout << "Zorkish :: Hall Of Fame" << std::endl;
    Console::Line();
    std::cout << "Top 10 Zorkish Adventure Champions" << std::endl;
    std::cout << "      1. Fred, Mountain World, 5000" << std::endl;
};
#include "About.h"

#include "MainMenu.h"

About About::m_AboutState;


std::string About::GetInput() {
    Console::AwaitEnter("Press Enter to return to the Main Menu");
    return "";
};
void About::Update(StateManager* stateManager, std::string input) {
    stateManager->SetState(MainMenu::Instance());
};
void About::Render() {
    system("cls"); // clear the console
    std::cout << "Zorkish :: About" << std::endl;
    Console::Line();
    std::cout << "Written by: Matthew Coulter" << std::endl;
};
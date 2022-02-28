#include "Help.h"

#include "MainMenu.h"
#include "Gameplay.h"

Help Help::m_HelpState;
std::string Help::GetInput() {
    Console::AwaitEnter("Press Enter to return to the Main Menu");
    return "";
};
void Help::Update(StateManager* stateManager, std::string input) {
    stateManager->SetState(MainMenu::Instance());
};
void Help::Render() {
    system("cls"); // clear the console
    std::cout << "Zorkish :: Help" << std::endl;
    Console::Line();
    std::cout << "The following commands are supported:" << std::endl;
    
    for (std::string command : Gameplay::Instance()->GetValidCommands()) {
        std::cout << "      " << command << std::endl;
    };
};
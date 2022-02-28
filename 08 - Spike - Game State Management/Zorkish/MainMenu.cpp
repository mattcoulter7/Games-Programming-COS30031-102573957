#include "MainMenu.h"

#include "SelectAdventure.h"
#include "HallOfFame.h"
#include "Help.h"
#include "About.h"

MainMenu MainMenu::m_MainMenuState;
std::string MainMenu::GetInput() {
	std::vector<std::string> validInputs = { "1","2","3","4","5" };
	return Console::AwaitValidatedInput(validInputs, "Select 1-" + std::to_string(validInputs.size()));
};
void MainMenu::Update(StateManager* stateManager, std::string input) {
    if (input == "1") {
        stateManager->SetState(SelectAdventure::Instance());
    }
    else if (input == "2") {
        stateManager->SetState(HallOfFame::Instance());
    }
    else if (input == "3") {
        stateManager->SetState(Help::Instance());
    }
    else if (input == "4") {
        stateManager->SetState(About::Instance());
    }
    else if (input == "5") {
        stateManager->Stop();
    }
};
void MainMenu::Render() {
    system("cls"); // clear the console
    std::cout << "Zorkish :: Main Menu" << std::endl;
    Console::Line();
    std::cout << "Welcome to Zorkish Adventures" << std::endl
        << "      1. Select Adventure and Play" << std::endl
        << "      2. Hall Of Fame" << std::endl
        << "      3. Help" << std::endl
        << "      4. About" << std::endl
        << "      5. Quit" << std::endl;
};
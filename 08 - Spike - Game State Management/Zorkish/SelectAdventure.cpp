#include "SelectAdventure.h"

#include "Gameplay.h"
SelectAdventure SelectAdventure::m_SelectAdventureState;

std::string SelectAdventure::GetInput() {
    std::vector<std::string> validInputs;
    for (auto const& x : Gameplay::Instance()->GetMaps()) {
        std::cout << "      " << x.first << ". " << x.second << std::endl;  // string (key)
        validInputs.push_back(x.first);
    }
    return Console::AwaitValidatedInput(validInputs, "Select 1-" + std::to_string(validInputs.size()));
};
void SelectAdventure::Update(StateManager* stateManager, std::string input) {
    Gameplay::Instance()->SetCurrentMap(input);
    stateManager->SetState(Gameplay::Instance());
};
void SelectAdventure::Render() {
    system("cls"); // clear the console
    std::cout << "Zorkish :: Select Adventure" << std::endl;
    Console::Line();
    std::cout << "Choose your adventure:" << std::endl;
};
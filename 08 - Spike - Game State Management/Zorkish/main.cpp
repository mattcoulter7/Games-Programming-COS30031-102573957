#include <string>

#include "StateManager.h"
#include "MainMenu.h"


int main() {
    StateManager zorkish = StateManager(
        MainMenu::Instance()
    );

    zorkish.Start();
    zorkish.Render();

    std::string input;
    while (zorkish.IsRunning()) {
        input = zorkish.GetInput();
        zorkish.Update(input);
        zorkish.Render();
    }

    return 0;
};
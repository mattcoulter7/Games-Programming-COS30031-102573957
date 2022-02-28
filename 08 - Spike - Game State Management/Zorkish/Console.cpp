#pragma once

#include "Console.h"

void Console::Line() {
    std::cout << "------------------------------------------------------------------------------------------" << std::endl << std::endl;
};
std::string Console::AwaitValidatedInput(std::vector<std::string> validStrings, std::string message) {
    std::cout << message << ":>";

    std::string input;
    std::cin >> input;
    toLowerCase(input);
    bool valid = false;
    for (auto validString : validStrings) {
        if (input == validString) {
            valid = true;
            break;
        }
    }
    if (!valid) {
        std::cout << "Input " << input << " is Invalid. Please try again." << std::endl;
        return AwaitValidatedInput(validStrings, message);
    }
    return input;
};

void Console::AwaitEnter(std::string message) {
    std::cout << message << std::endl;
    _getch();
};

void Console::toLowerCase(std::string& value) {
    for (std::string::size_type i = 0; i < value.size(); ++i) {
        value[i] = tolower(value[i]);
    }
};

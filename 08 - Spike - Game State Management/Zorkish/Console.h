#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

class Console {
    public:

        static void Line();
        static std::string AwaitValidatedInput(std::vector<std::string> validStrings, std::string message);
        static void AwaitEnter(std::string message);
    private:
        static void toLowerCase(std::string& value);
};

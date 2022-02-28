#include <iostream>
#include <conio.h>

int main() {
    while(1)
    {
        int input = getch();
        if(input)
        {
            std::cout << input;
        }
    }
}
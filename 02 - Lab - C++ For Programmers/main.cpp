#include <chrono>
#include <random>
#include <iostream>
#include <string>
#include <array>
#include "Person.h"

//#region Task 1
void displayTwoValues(int value1, int value2){
    std::cout << "Value 1 is " << value1 << std::endl;
    std::cout << "Value 2 is " << value2 << std::endl;
}
//#endregion

//#region Task 2
int alterOneValue(int value){
    // simple modification of +1
    return value + 1;
}
//#endregion

//#region Task 3
void alterOnePointedValue(int* value){
    // simple modification of +1
    *value += 1;
}
//#endregion

//#region Task 4
void printOddNumbersUntil(int end = 20){
    // loop until end, if number is odd print it
    for (int i = 0; i < end; i++){
        if (i % 2 == 1){
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
}
//#endregion

//#region Task 5

void fillRandomArray(int length = 5){
    std::array<int, 5> arr;

    // set the random numbers
    for (int i = 0; i < length; i++)
    {
        arr[i] = rand();
    }

    // print the array
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}
//#endregion

//#region Task 6

void splitString(std::string str,char delim = ' '){
    std::string currentWord = "";
    for (int i = 0; i < str.size(); i++){
        char currentLetter = str[i];
        if (currentLetter == delim){
            std::cout << currentWord << std::endl;
            currentWord = "";
        } else {
            currentWord.push_back(currentLetter);
        }
    }
    std::cout << currentWord << std::endl; // print last word as no space at very end
}
//#endregion



// start
int main()
{
    // generate random number seed
    srand((unsigned int)time(NULL));

    // Run Task 1
    std::cout << "1. Create a function that accepts at least two values (simple parameter values, not user input), prints the values to screen, and returns nothing. Call this function from your main. " << std::endl;
    displayTwoValues(3,5);
    std::cout << "\n";

    // Run Task 2
    std::cout << "2. Create a function that accepts one value, alters it, and returns it (simple value). Call this function from main, and print the returned value. " << std::endl;
    int val = 10;
    std::cout << "Original value is: " << val << std::endl;
    std::cout << "Altered value is: " << alterOneValue(val) << std::endl;
    std::cout << "\n";

    // Run Task 3
    std::cout << "3. Declare a pointer to a variable, and demonstrate the setting and reading of the value in the variable using the pointer." << std::endl;
    int *pointerVal = &val;
    std::cout << "Original value is: " << val << std::endl;
    alterOnePointedValue(pointerVal);
    std::cout << "Altered (pointed value) value is: " << val << std::endl;
    std::cout << "\n";
    
    // Run Task 4
    std::cout << "4. Create a function that uses a for loop to print all odd numbers between 0 and 20 on a single text line of text output, formatted with spaces. Call this from main." << std::endl;
    printOddNumbersUntil();
    std::cout << "\n";
    
    // Run Task 5
    std::cout << "5. Create a function that creates a 1-dimensional array of 5 integers, then fill the array with random int values, print the contents of the array to the screen. Call from main." << std::endl;
    fillRandomArray();
    std::cout << "\n";
    
    // Run Task 6
    std::cout << "6. Split the line of text, such as 'this has spaces in it', by spaces, and show each part to screen." << std::endl;
    std::string strToSplit("this has spaces in it");
    splitString(strToSplit);
    std::cout << "\n";
    
    // Run Task 7
    std::cout << "7. Declare a simple class that has at least one private variable, one public variable, and one public method. Create an instance of the class, and demonstrate its use." << std::endl;
    Person* p = new Person("Jeff",21);
    p->favouriteFood = "Gummy Bears";
    std::cout << p->getName() << " is currently " << p->getAge() << " years old" << std::endl;
    p->grow();
    std::cout << p->getName() << " grew up and is now " << p->getAge() << " years old" << std::endl;
    std::cout << p->getName() << "'s favourite food is " << p->favouriteFood << std::endl;

    std::cout << "\n";
    
    // end
    std::string pause;
    std::cin >> pause;

    return 0;
}
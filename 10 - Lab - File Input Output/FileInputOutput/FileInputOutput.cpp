#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "json.hpp"
using json = nlohmann::json;

#define number_bits 3

struct Person {
    char initial;
    int age;
    float weight;

    void Print() {
        std::cout <<    "Initial is "   << initial << std::endl <<
                        "Age is "       << age     << std::endl <<
                        "Weight is "    << weight  << std::endl << std::endl;
    }
};

typedef std::vector<std::string> split;
split SplitString(std::string str, char delim = ' ') {
    split words;
    std::string currentWord = "";
    for (int i = 0; i < str.size(); i++) {
        char currentLetter = str[i];
        if (currentLetter == delim) {
            words.push_back(currentWord);
            currentWord = "";
        }
        else {
            currentWord.push_back(currentLetter);
        }
    }
    words.push_back(currentWord);
    return words;
}



int main()
{
    /* PART A */ 
    //write the binary file
    if (false) {
        Person foo = { 'M', 80, 67.8 };
        foo.Print();
        
        // a.open a binary file in “write” mode(such as “test1.bin”), then
        std::ofstream outfile;
        outfile.open("test1.bin", std::ios::binary | std::ios::out);
        
        // b.write the three different values to the binary file, and finally
        outfile.write(reinterpret_cast<const char*>(&foo), sizeof(foo));
        
        // c.close the file.
        outfile.close();
    }

    // read the binary file
    if (false) {
        Person foo;

        // open a binary file in read mode
        std::ifstream infile;
        infile.open("test1.bin", std::ios::binary | std::ios::in);

        // read the file into foo variable
        infile.read(reinterpret_cast<char*>(&foo), sizeof(foo));

        // print the read data
        foo.Print();

        //close the file
        infile.close();
    }



    /* PART B */
    if (false) {
        // a.Open the file(text mode, read only),
        std::ifstream infile;
        infile.open("test2.txt", std::ios::in);
        // b.Print each line to screen, one at a time
        std::string line;
        while (!infile.eof())
        {
            std::getline(infile, line);

            // Ignore any blank line(“strip” whitespace first ? ),
            if (line == "") continue;
            
            // Ignore a line that starts with the hash “#” character(treats it as a single line comment),
            if (line[0] == '#') continue;
            
            // Splits all other lines, checking that is has the appropriate number of “bits”, and
            split bits = SplitString(line,':');
            if (bits.size() != number_bits) continue;
            
            // Prints each split line to screen, on bit at a time. (The “bits” are just strings in this case.)
            for (std::string bit : bits)
                std::cout << bit << std::endl;

            std::cout << std::endl;
        }
    }

    /* PART C */
    if (true) {
        // a.Open the file(text mode, read only),
        std::ifstream infile;
        infile.open("test3.json", std::ios::in);
        
        // b.load content into file
        std::string content((std::istreambuf_iterator<char>(infile)),(std::istreambuf_iterator<char>()));

        // c. parse the json string into the json object
        auto jObject = json::parse(content);

        // d. print the output
        for (auto it = jObject.begin(); it != jObject.end(); ++it) {
            std::cout << it.key() << ": " << it.value() << std::endl;
        }
    }
    return 0;
};
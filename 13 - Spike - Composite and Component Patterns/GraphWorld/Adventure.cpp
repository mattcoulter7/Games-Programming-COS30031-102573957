#include "Adventure.h"

bool Adventure::LoadFile(std::string dir) {
    if (!std::filesystem::exists(dir)) {
        std::cout << "File: " << dir << " Does not exist." << std::endl;
        return false;
    }

    // a.Open the file(text mode, read only),
    std::ifstream infile;
    infile.open(dir, std::ios::in);

    // b.load content into file
    std::string content((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));

    // c. parse the json string into the json object
    auto jObject = json::parse(content);

    for (json world : jObject) {
        AddWorld(new World(world));
    }
    return true;
}
void Adventure::LoadFile() {
    std::cout << "Please enter file name to load (json)" << std::endl;
    std::string dir; 
    std::getline(std::cin,dir);
    while (!LoadFile(dir)) {
        std::cout << "Please Try Again" << std::endl;
        std::getline(std::cin, dir);
    }
}

World* Adventure::GetWorld(int id) {
    for (World* w : worlds)
        if (w->GetId() == id)
            return w;
    return nullptr;
}

void Adventure::AddWorld(World* world) {
    worlds.push_back(world);
}

void Adventure::PlayWorld(int id) {
    World* w = GetWorld(id);
    if (w == nullptr) {
        std::cout << "World with id " << id << " does not exist." << std::endl;
        return;
    }
    w->Play();
}
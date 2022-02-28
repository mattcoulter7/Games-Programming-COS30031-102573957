#include "PrefabManager.h"

#include <fstream>
#include <iostream>

#include "ComponentTypeFactory.h"

void PrefabManager::Load(std::string path) {
    // a.Open the file(text mode, read only),
    std::ifstream infile;
    infile.open(path, std::ios::in);

    // b.load content into file
    std::string content((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));

    // c. parse the json string into the json object
    auto jObject = json::parse(content);

    for (json prefab : jObject) {

        std::vector<BaseComponent*> components = ComponentTypeFactory::Instance()->CreateFromJsonArray(prefab["_components"]);
        // create the prefab
        size_t id = prefab["id"];
        std::string name = prefab["name"];
        
        _prefabs[id] = new Prefab(id,name,components);
        _prefabs[id]->rawJSON = new json(prefab); // create a copy of the json and save it against the prefab
    }
}
Prefab* PrefabManager::GetPrefab(size_t id) {
    return _prefabs[id];
}
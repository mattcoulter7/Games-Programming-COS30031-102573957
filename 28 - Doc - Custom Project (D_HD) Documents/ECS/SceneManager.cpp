#include "SceneManager.h"

#include <fstream>
#include <iostream>

#include "ECS.h"

void SceneManager::LoadScene(std::string path, std::string id) {
    // a.Open the file(text mode, read only),
    std::ifstream infile;
    infile.open(path, std::ios::in);

    // b.load content into file
    std::string content((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));

    // c. parse the json string into the json object
    auto jObject = json::parse(content);

    // get the scene from the id
    json sceneJson = jObject[id];

    json entities = sceneJson["entities"];
    for (json& obj : entities) {
        // create the entity
        Entity* entity = ECS::ECS_ENGINE()->GetEntityManager()->AddEntityFromJson(obj);
        // get the entity components and prefab components
        json entityComponents = obj["_components"];
        json prefabComponents;
        if (!obj["prefabid"].is_null()) {
            // get the prefab data
            Prefab* prefab = ECS::ECS_ENGINE()->GetPrefabManager()->GetPrefab(obj["prefabid"]);
            prefabComponents = (*prefab->rawJSON)["_components"];
            entity->prefabid = obj["prefabid"];

            // exclude entity components linked to prefab components, copy values over etc.
            CombineEntityPrefabComponents(prefabComponents, entityComponents);
        }

        // Add Prefab Components to the entity
        if (!prefabComponents.is_null()) {
            ECS::ECS_ENGINE()->GetComponentManager()->AddComponents(entity->GetId(), 
                ComponentTypeFactory::Instance()->CreateFromJsonArray(prefabComponents)
            );
        }
        // Add Entity Component to the entity
        if (!entityComponents.is_null()) {
            ECS::ECS_ENGINE()->GetComponentManager()->AddComponents(entity->GetId(),
                ComponentTypeFactory::Instance()->CreateFromJsonArray(entityComponents)
            );
        }
    }
}


void SceneManager::CombineEntityPrefabComponents(json& prefabComponents, json& entityComponents) {
    // add entity component changes to the prefab (if it exists!)
    if (!prefabComponents.is_null() && !entityComponents.is_null()) {
        // apply entity component modifications to the prefab json object
        for (auto it = entityComponents.begin(); it != entityComponents.end();) {
            json& entityComp = it.value();
            if (!entityComp["prefabcomponentid"].is_null()) {
                json* prefabComponent = nullptr;
                // find the prefab component with the matching id
                for (json& prefabComp : prefabComponents) {
                    if (prefabComp["prefabcomponentid"] == entityComp["prefabcomponentid"]) {
                        prefabComponent = &prefabComp;
                    }
                }

                // prefab component found, combine entity values to it
                if (prefabComponent != nullptr) {
                    json_extension::combine(*prefabComponent, entityComp);
                }

                // remove from the entity obj as change have been applied to the prefab copy
                it = entityComponents.erase(it);
            }
            else {
                // loop only when it doesn't get removed
                ++it;
            }

        }
    }
}
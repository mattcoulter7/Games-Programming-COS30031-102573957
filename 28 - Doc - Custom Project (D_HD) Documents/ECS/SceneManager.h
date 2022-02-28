#pragma once

/*
	Handle loading in a scene and all of its entities
*/
#include <string>

#include "json_extension.hpp"

class SceneManager {
public:
	void LoadScene(std::string path, std::string id);
	void CombineEntityPrefabComponents(json& prefabComponents, json& entityComponents);
};
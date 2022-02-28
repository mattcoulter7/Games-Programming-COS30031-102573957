/*
	Handle creating entities from a prefab
*/

#include "Prefab.h"

class PrefabManager {
public:
	void Load(std::string path);
    Prefab* GetPrefab(size_t id);
private:
	std::map<size_t, Prefab*> _prefabs; // prefabs are saved as json
};
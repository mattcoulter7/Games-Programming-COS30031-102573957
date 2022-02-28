#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "PrefabManager.h"
#include "SceneManager.h"
#include "Instantiator.h"

class ECS {
public:
	ECS();
	~ECS();
	EntityManager* GetEntityManager();
	ComponentManager* GetComponentManager();
	SystemManager* GetSystemManager();
	PrefabManager* GetPrefabManager();
	SceneManager* GetSceneManager();
	Instantiator* GetInstantiator();
	static ECS* ECS_ENGINE();
	bool IsRunning();
	void Start();
	void Stop();
	bool debug = true; // shows useful debug info
private:
	EntityManager* _entityManager;
	ComponentManager* _componentManager;
	SystemManager* _systemManager;
	PrefabManager* _prefabManager;
	SceneManager* _sceneManager;
	Instantiator* _instantiator;
	static ECS _instance;
	bool _running = false;
};
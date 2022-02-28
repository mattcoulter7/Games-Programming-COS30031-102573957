#pragma once

#include "ECS.h"

ECS::ECS() {
	_entityManager = new EntityManager();
	_componentManager = new ComponentManager();
	_systemManager = new SystemManager();
	_prefabManager = new PrefabManager();
	_sceneManager = new SceneManager();
	_instantiator = new Instantiator();
}
ECS::~ECS() {
	delete _entityManager;
	delete _componentManager;
	delete _systemManager;
	delete _prefabManager;
	delete _sceneManager;
}
EntityManager* ECS::GetEntityManager() {
	return _entityManager;
};
ComponentManager* ECS::GetComponentManager() {
	return _componentManager;
};
SystemManager* ECS::GetSystemManager() {
	return _systemManager;
};
PrefabManager* ECS::GetPrefabManager() {
	return _prefabManager;
};
SceneManager* ECS::GetSceneManager() {
	return _sceneManager;
}
Instantiator* ECS::GetInstantiator() {
	return _instantiator;
}

bool ECS::IsRunning() {
	return _running;
};
void ECS::Start() {
	_running = true;
}
void ECS::Stop() {
	_running = false;
}

ECS ECS::_instance;
ECS* ECS::ECS_ENGINE() {
	return &_instance;
};
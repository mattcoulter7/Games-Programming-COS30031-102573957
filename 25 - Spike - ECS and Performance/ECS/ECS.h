#pragma once

#include "EntityManager.cpp"
#include "SystemManager.cpp"
#include "ComponentManager.cpp"

class ECS {
public:
	ECS();
	~ECS();
	EntityManager* GetEntityManager();
	ComponentManager* GetComponentManager();
	SystemManager* GetSystemManager();
	static ECS* ECS_ENGINE();
	bool IsRunning();
	void Start();
	void Stop();
private:
	EntityManager* _entityManager;
	ComponentManager* _componentManager;
	SystemManager* _systemManager;
	static ECS* m_instance;
	bool _running = false;
};
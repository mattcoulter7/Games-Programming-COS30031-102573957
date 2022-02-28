#pragma once

#include "ECS.h"

ECS::ECS() {
	_entityManager = new EntityManager();
	_componentManager = new ComponentManager();
	_systemManager = new SystemManager();
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


bool ECS::IsRunning() {
	return _running;
};
void ECS::Start() {
	_running = true;
}
void ECS::Stop() {
	_running = false;
}
ECS* ECS::m_instance;
ECS* ECS::ECS_ENGINE() {
	if (m_instance == nullptr) {
		m_instance = new ECS();
	}
	return m_instance;
};
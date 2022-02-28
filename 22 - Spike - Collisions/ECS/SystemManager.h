#pragma once

#include <map>

#include "System.h"

class SystemManager {
public:
	template <class T, typename ...Args>
	T* AddSystem(Args... args) {  // add a new component of type T
		size_t sysType = System::GetType<T>();
		T* system = new T(args...);
		_systems[sysType] = system;
		return system;
	};
	template <class T>
	T* GetSystem() { // first instance of component of type T
		size_t sysType = System::GetType<T>();
		System* system = _systems[sysType];
		return static_cast<T*>(system);
	};
	template <class T>
	void RemoveSystem() { // first instance of component of type T
		size_t sysType = System::GetType<T>();
		System* system = _systems[sysType];
		if (system != nullptr) {
			delete system;
			_systems.erase(sysType);
		}
	};

	void Update(double dt) {
		for (auto &pair : _systems) {
			System* sys = pair.second;
			sys->Update(dt);
		}
	}

	void Render(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		for (auto& pair : _systems) {
			System* sys = pair.second;
			sys->Render(renderer);
		}
		SDL_RenderPresent(renderer);
	}

private:
	std::map<size_t,System*> _systems;
};
#pragma once

#include "SystemTypeFactory.h"

#include <fstream>
#include <iostream>

class SystemManager {
public:
	~SystemManager() {
		for (auto& pair : _systems) {
			delete pair.second;
		}
	}
	template <class T>
	T* AddSystem() {  // add a new system of type T
		std::type_index sysType = typeid(T);
		T* system = SystemTypeFactory::Instance()->Create<T>();
		AddSystem(system);
	};
	template <class T>
	T* GetSystem() { // first instance of system of type T
		std::type_index sysType = typeid(T);
		System* system = _systems[sysType];
		return static_cast<T*>(system);
	};
	template <class T>
	void RemoveSystem() { // first instance of system of type T
		std::type_index sysType = typeid(T);
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

	// loads all the systems from a file
	void Load(std::string path) {
		// a.Open the file(text mode, read only),
		std::ifstream infile;
		infile.open(path, std::ios::in);

		// b.load content into file
		std::string content((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));

		// c. parse the json string into the json object
		auto jObject = json::parse(content);

		for (json system : jObject) {
			System* sys = SystemTypeFactory::Instance()->CreateFromJson(system);
			AddSystem(sys);
		}
	}

private:
	void AddSystem(System* system) {  // add a new system of type T
		std::type_index sysType = typeid(*system);
		_systems[sysType] = system;
	};
	std::map<std::type_index,System*> _systems;
};
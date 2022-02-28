#pragma once

#include "ComponentManager.h"
#include "SDL.h"
#undef main

#include <iostream>
#include <vector>
#include <typeinfo>

class System {
public:
	virtual void Update(double dt) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

	template<class T>
	static size_t GetType() {
		return typeid(T).hash_code();
	}
};
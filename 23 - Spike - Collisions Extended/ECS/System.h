#pragma once

#include <iostream>
#include <vector>
#include <typeinfo>
#include <map>

#include "SDL.h"
#undef main

class System {
public:
	virtual void Update(double dt) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

	template<class T>
	static size_t GetType() {
		return typeid(T).hash_code();
	}
};
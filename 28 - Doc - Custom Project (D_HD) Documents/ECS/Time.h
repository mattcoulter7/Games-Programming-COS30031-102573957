#pragma once

#include <iostream>

#include "SDL.h"

struct Time {
public:
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;
	double frameRate = 0;
	double frameCount = 0;
	double startTime = SDL_GetPerformanceCounter();
	double performanceRunTime = 0;
	double runTime = 0;
	static Time* Instance() {
		return &_instance;
	}
private:
	static Time _instance;
};
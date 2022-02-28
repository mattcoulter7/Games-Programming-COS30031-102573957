#pragma once

#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL.h>
#undef main

#include "System.h"

class Render2DSystem : public System {
public:
	Render2DSystem();
	void Update(ComponentManager* cm) override;
	void Render(ComponentManager* cm) override;
	SDL_Window* window;
	SDL_Renderer* renderer;
	float width;
	float height;
};
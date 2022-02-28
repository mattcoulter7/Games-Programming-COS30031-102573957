#pragma once

#include <SDL_mixer.h>
#include <SDL_image.h>

#include "System.h"

class Render2DSystem : public System {
public:
	Render2DSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
	SDL_Window* window;
	SDL_Renderer* renderer;
	float width;
	float height;
};
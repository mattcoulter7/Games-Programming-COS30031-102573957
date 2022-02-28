#pragma once

#include "System.h"

#include <SDL_mixer.h>
#include <SDL_image.h>

class Render2DSystem : public System {
public:
	Render2DSystem();
	Render2DSystem(json obj);
	~Render2DSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
	SDL_Window* window;
	SDL_Renderer* renderer;
	float width = 800;
	float height = 600;
private:
	void AddEventListeners() override;
};
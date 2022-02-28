#pragma once

#include <SDL_mixer.h>
#include <SDL_image.h>

#include "ECS.h"

#include "Transform2D.h"
#include "SpriteRenderer2D.h"

class Render2DSystem : public System {
public:
	Render2DSystem();
	void Update(double dt) override;
	void Render(SDL_Renderer* renderer) override;
	SDL_Window* window;
	SDL_Renderer* renderer;
	float width = 800;
	float height = 600;
};
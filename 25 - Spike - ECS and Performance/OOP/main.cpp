#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "Vector2.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

float RandomRange(int min, int max) {
	return rand() % (max - min + 1) + min;
}
struct Entity {
	Vector2 pos;
	Vector2 vel;
	float radius = 16;
	SDL_Rect src;
	SDL_Rect dest;
	SDL_Surface* surface;
	SDL_Texture* texture;
};
std::vector<Entity> entities;
double numEntities = 0;

void AddEntity(SDL_Renderer* renderer) {
	Entity ent;
	// inital random position and velocity
	ent.vel = Vector2{ RandomRange(-100,100) / 100,RandomRange(-100,100) / 100 };
	ent.pos = Vector2{ RandomRange(0,SCREEN_WIDTH),RandomRange(0,SCREEN_HEIGHT) };
	// cache the sprite
	ent.src.x = 0;
	ent.src.y = 0;
	ent.src.w = 32;
	ent.src.h = 32;
	ent.dest.w = 32; // centered
	ent.dest.h = 32; // centered
	ent.surface = IMG_Load("assets/player.png");
	ent.texture = SDL_CreateTextureFromSurface(renderer, ent.surface);
	++numEntities;
	entities.push_back(ent);
}

void UpdateEntities(double dt) {
	// update velocity for when bouncing into wall
	for (Entity& e : entities) {
		// update position
		e.pos += e.vel * dt;

		// reposition sprite
		e.dest.x = e.pos.x;
		e.dest.y = e.pos.y;

		// bounce with edge of screen
		if (e.pos.x >= SCREEN_WIDTH || e.pos.x <= 0) {
			e.vel.x = -e.vel.x;
		}
		if (e.pos.y >= SCREEN_HEIGHT || e.pos.y <= 0) {
			e.vel.y = -e.vel.y;
		}
	}
}

void RenderEntities(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	for (Entity& e : entities) {
		SDL_RenderCopy(renderer, e.texture, &e.src, &e.dest);
	}
	SDL_RenderPresent(renderer);
}

int main(int argc, char** argv) {
	srand(time(NULL)); // Seed the time

	// create the SDL window and renderer
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	// performance parameters
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;
	double frameRate = 0;
	double frameCount = 0;
	double startTime = NOW;
	double runTime = 0;
	SDL_Event event;

	// game loop
	bool quit = false;
	while (!quit)
	{
		// recalculate performance parameters
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		runTime = NOW - startTime;
		frameRate = frameCount / (runTime / 10000000);
		std::cout << frameRate << ": " << numEntities << std::endl;

		// add a new entity
		AddEntity(renderer);

		// handle sdl events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		// update
		UpdateEntities(deltaTime);

		// render
		RenderEntities(renderer);
		++frameCount;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
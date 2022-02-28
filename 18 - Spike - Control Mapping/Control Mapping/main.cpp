#include "StateManager.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
StateManager game;

int main(int argc, char** argv) {
	// create the SDL window and renderer
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	SDL_Event event;
	// initial render
	game.Render();

	// game loop
	bool quit = false;
	while (!quit)
	{
		// handle sdl events
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN: case SDL_MOUSEBUTTONDOWN:
					// Handle mouse clicks here.
					game.Update(event);
					game.Render();
					break;

				case SDL_QUIT:
					quit = true;
					break;

				default:
					break;
			}   // End switch
		}

		// render sdl window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// render things here
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
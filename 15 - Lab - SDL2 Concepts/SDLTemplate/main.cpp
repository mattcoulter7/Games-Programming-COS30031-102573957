#include <SDL.h>
#include <iostream>
#include <random>

int main(int argc, char* args[])
{
    // init the sdl
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // ensure sdl exitting is properly handled
    atexit(SDL_Quit);

    // create the window and renderer
    SDL_Window* window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // initial render of plain color
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // variable holding the event
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        // handle all events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    // if input is 'r', set the background to a random color
                    if (event.key.keysym.sym == 'r') {
                        SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255);
                        SDL_RenderClear(renderer);
                        SDL_RenderPresent(renderer);
                    }
                    break;
                case SDL_KEYUP:
                    break;
                // sdl quit is when they close the tab, this should also close the console application running in the background
                case SDL_QUIT:
                    quit = 1;
                    break;
                default:
                    break;
            }

        }
    }

    return 0;
}
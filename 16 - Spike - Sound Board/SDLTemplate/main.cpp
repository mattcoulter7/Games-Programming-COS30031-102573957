#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);

    // create the window and renderer
    SDL_Window* window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // load audio files
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Music* sample1 = Mix_LoadMUS("Chopin Black Keys.wav");
    Mix_Music* sample2 = Mix_LoadMUS("Mojito.wav");
    Mix_Music* sample3 = Mix_LoadMUS("Spain.wav");
    
    // variable holding the event
    SDL_Event event;
    int quit = 0;
    int playing = 0;
    while (!quit) {
        // handle all events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case '1':
                            Mix_PlayMusic(sample1,0);
                            break;
                        case '2':
                            Mix_PlayMusic(sample2, 0);
                            break;
                        case '3':
                            Mix_PlayMusic(sample3, 0);
                            break;
                        case '0':
                            if (Mix_PausedMusic() == 1) {
                                Mix_ResumeMusic();
                            }
                            else {
                                Mix_PauseMusic();
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
                default:
                    break;
                }

        }
    }

    Mix_FreeMusic(sample1);
    Mix_FreeMusic(sample2);
    Mix_FreeMusic(sample3);
    Mix_CloseAudio();
	return 0;
}
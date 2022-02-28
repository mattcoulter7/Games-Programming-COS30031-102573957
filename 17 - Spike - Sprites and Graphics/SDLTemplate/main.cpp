#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL.h>
#include <iostream>


int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);

    const int SCREEN_WIDTH = 600;
    const int SCREEN_HEIGHT = 400;

    // create the window and renderer
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    // load the background
    SDL_Surface* backgroundSurface = IMG_Load("assets/background.png");
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_Rect backgroundSrc;// size of original image
    backgroundSrc.x = 0;
    backgroundSrc.y = 0;
    backgroundSrc.w = 1001;
    backgroundSrc.h = 1001;
    SDL_Rect backgroundDest; // background destination is position&size on screen to render to
    backgroundDest.x = 0;
    backgroundDest.y = 0;
    backgroundDest.w = SCREEN_WIDTH;
    backgroundDest.h = SCREEN_HEIGHT;

    // load the player
    SDL_Surface* playerSurface = IMG_Load("assets/player.png");
    SDL_Texture* playerSpritesheet = SDL_CreateTextureFromSurface(renderer, playerSurface);
    const int playerSpriteSquare = 256;
    
    // first in spritesheet
    SDL_Rect playerSrc1;
    playerSrc1.x = playerSpriteSquare * 0;
    playerSrc1.y = 0;
    playerSrc1.w = playerSpriteSquare;
    playerSrc1.h = playerSpriteSquare;
    
    // second in spritesheet
    SDL_Rect playerSrc2;
    playerSrc2.x = playerSpriteSquare * 1;
    playerSrc2.y = 0;
    playerSrc2.w = playerSpriteSquare;
    playerSrc2.h = playerSpriteSquare;
    
    // third in spritesheet
    SDL_Rect playerSrc3;
    playerSrc3.x = playerSpriteSquare * 2;
    playerSrc3.y = 0;
    playerSrc3.w = playerSpriteSquare;
    playerSrc3.h = playerSpriteSquare;

    // position on screen
    SDL_Rect playerDest;
    playerDest.w = 128;
    playerDest.h = 128;
    playerDest.x = (SCREEN_WIDTH / 2) - (playerDest.w / 2); // centered
    playerDest.y = (SCREEN_HEIGHT / 2) - (playerDest.h / 2); // centered

    // pointer to which sprite rectangle is currently being used
    SDL_Rect* activePlayerSrc = &playerSrc1; // which every sprite should be rendered

    // variable holding the event
    SDL_Event event;
    int quit = 0;
    bool playerVisible = false;
    while (!quit) {
        // handle all events and perform updates
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case '1':
                    activePlayerSrc = &playerSrc1;
                    break;
                case '2':
                    activePlayerSrc = &playerSrc2;
                    break;
                case '3':
                    activePlayerSrc = &playerSrc3;
                    break;
                case '0':
                    playerVisible=!playerVisible;
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

        // render process
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, &backgroundSrc, &backgroundDest); //render background
        if (playerVisible) {
            SDL_RenderCopy(renderer, playerSpritesheet, activePlayerSrc, &playerDest); // render player
        }
        SDL_RenderPresent(renderer);
    }

	return 0;
}
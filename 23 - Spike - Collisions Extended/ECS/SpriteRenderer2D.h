#pragma once

#include "BaseComponent.h"

#include <SDL_image.h>

// renders the entity
struct SpriteRenderer2D : public BaseComponent {
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Surface* surface;
    SDL_Texture* texture;
};
#pragma once

#include "BaseComponent.h"

#include "SDL.h"
#include <SDL_image.h>

// renders the entity
struct SpriteRenderer2D : public BaseComponent {
    SpriteRenderer2D() : BaseComponent() {}
    SpriteRenderer2D(const SpriteRenderer2D& obj) : BaseComponent(obj) {
        src = obj.src;
        dest = obj.dest;
        path = obj.path;
        offset = obj.offset;
        surface = IMG_Load(path.c_str());
    };
    SpriteRenderer2D(json obj) : BaseComponent(obj) {
        if (!obj["path"].is_null()) {
            path = obj["path"];
            surface = IMG_Load(path.c_str());
        }

        src.x = obj["src"]["x"].is_null() ? src.x : obj["src"]["x"];
        src.y = obj["src"]["y"].is_null() ? src.y : obj["src"]["y"];
        src.w = obj["src"]["w"].is_null() ? src.w : obj["src"]["w"];
        src.h = obj["src"]["h"].is_null() ? src.h : obj["src"]["h"];

        dest.x = obj["dest"]["x"].is_null() ? dest.x : obj["dest"]["x"];
        dest.y = obj["dest"]["y"].is_null() ? dest.y : obj["dest"]["y"];
        dest.w = obj["dest"]["w"].is_null() ? dest.w : obj["dest"]["w"];
        dest.h = obj["dest"]["h"].is_null() ? dest.x : obj["dest"]["h"];

        offset.x = obj["offset"]["x"].is_null() ? offset.x : obj["offset"]["x"];
        offset.y = obj["offset"]["y"].is_null() ? offset.y : obj["offset"]["y"];
    } // json constructor
    ~SpriteRenderer2D() {
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
    BaseComponent* Clone() {
        return new SpriteRenderer2D(*this);
    };
    std::string path = "";
    Vector2 offset{ 0,0 };
    SDL_Rect src{0,0,0,0};
    SDL_Rect dest{0,0,0,0};
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
};
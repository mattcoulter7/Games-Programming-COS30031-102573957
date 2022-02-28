#pragma once

#include "Render2DSystem.h"

#include "ECS.h"
#include "Debug.h"
#include "SpriteRenderer2D.h"
#include "Transform2D.h"

Render2DSystem::Render2DSystem() : System() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	AddEventListeners();
};

Render2DSystem::Render2DSystem(json obj) : System(obj) {
	width = obj["width"].is_null() ? width : obj["width"];
	height = obj["height"].is_null() ? height : obj["height"];

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

	AddEventListeners();
}
Render2DSystem::~Render2DSystem() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};
void Render2DSystem::AddEventListeners() {}

void Render2DSystem::Update(double dt) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	// ensure render is based on transform component
	std::vector<SpriteRenderer2D*> spriteRenderers = cm->GetComponents<SpriteRenderer2D>();
	for (SpriteRenderer2D* sr2d : spriteRenderers) {
		Transform2D* tf = cm->GetComponent<Transform2D>(sr2d->entityid);
		Vector2 offset = sr2d->offset;
		if (tf != nullptr) {
			offset.RotateRadians(tf->rotation);

			sr2d->dest.x = tf->position.x + offset.x;
			sr2d->dest.y = tf->position.y + offset.y;
		}
	}
}
void Render2DSystem::Render(SDL_Renderer* renderer) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();

	// get all the SpriteRenderer2D components
	std::vector<SpriteRenderer2D*> spriteRenderers = cm->GetComponents<SpriteRenderer2D>();
	// render them
	for (SpriteRenderer2D* sr2d : spriteRenderers) {
		// ensure the texture is loaded

		if (sr2d->texture == NULL) {
			sr2d->texture = SDL_CreateTextureFromSurface(renderer, sr2d->surface);
		}
		Transform2D* tf = cm->GetComponent<Transform2D>(sr2d->entityid);
		
		double degrees =  tf->rotation * 180 / M_PI;

		SDL_Point rotateAround{ sr2d->src.x,sr2d->src.y };
		SDL_RenderCopyEx(renderer, sr2d->texture, &sr2d->src, &sr2d->dest, degrees, &rotateAround, SDL_FLIP_NONE);
	}
}
#pragma once

#include "Render2DSystem.h"

#include "ECS.h"

#include "Transform2D.h"
#include "SpriteRenderer2D.h"

Render2DSystem::Render2DSystem() : System() {
	SDL_Init(SDL_INIT_EVERYTHING);
	atexit(SDL_Quit);

	// create the window and renderer
	SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
};
void Render2DSystem::Update(double dt) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();
	// ensure render is based on transform component
	std::vector<SpriteRenderer2D*> spriteRenderers = cm->GetComponents<SpriteRenderer2D>();
	for (SpriteRenderer2D* sr2d : spriteRenderers) {
		Transform2D* tf = cm->GetComponent<Transform2D>(sr2d->entityid);
		if (tf != nullptr) {
			sr2d->dest.x = tf->position.x;
			sr2d->dest.y = tf->position.y;
		}
	}
}
void Render2DSystem::Render(SDL_Renderer* renderer) {
	ComponentManager* cm = ECS::ECS_ENGINE()->GetComponentManager();

	// get all the SpriteRenderer2D components
	std::vector<SpriteRenderer2D*> spriteRenderers = cm->GetComponents<SpriteRenderer2D>();
	// render them
	for (SpriteRenderer2D* sr2d : spriteRenderers) {
		SDL_RenderCopy(renderer, sr2d->texture, &sr2d->src, &sr2d->dest);
	}

}
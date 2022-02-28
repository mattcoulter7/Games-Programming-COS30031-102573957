#include <iostream>

#include "ECS.h"

// systems
#include "PhysicsSystem.h"
#include "Render2DSystem.h"
#include "Collider2DSystem.h"

// components
#include "RigidBody2D.h"
#include "SpriteRenderer2D.h"
#include "Transform2D.h"
#include "CircleCollider.h"

Entity* AddPlayer(Vector2 pos,Vector2 vel) {
	ECS* ecs = ECS::ECS_ENGINE();

	EntityManager* em = ecs->GetEntityManager(); //E
	ComponentManager* cm = ecs->GetComponentManager(); //C
	SystemManager* sm = ecs->GetSystemManager(); //SS

	// get systems
	Render2DSystem* renderSystem = sm->GetSystem<Render2DSystem>();

	// add player
	Entity* player = em->AddEntity();

	// add transform
	Transform2D* playerTransform = cm->AddComponent<Transform2D>(player->GetId());
	playerTransform->position = pos;

	// add rigid body
	RigidBody2D* playerRB = cm->AddComponent<RigidBody2D>(player->GetId());
	playerRB->velocity = vel;
	playerRB->gravityScale = 0.000; // 05;

	// renderer
	SpriteRenderer2D* playerSprite = cm->AddComponent<SpriteRenderer2D>(player->GetId());
	playerSprite->src.x = 0;
	playerSprite->src.y = 0;
	playerSprite->src.w = 256;
	playerSprite->src.h = 256;
	playerSprite->dest.w = 128; // centered
	playerSprite->dest.h = 128; // centered
	playerSprite->surface = IMG_Load("assets/player.png");
	playerSprite->texture = SDL_CreateTextureFromSurface(renderSystem->renderer, playerSprite->surface);

	return player;
}


int main(int argc, char** argv) {
	ECS* ecs = ECS::ECS_ENGINE();

	EntityManager* em = ecs->GetEntityManager(); //E
	ComponentManager* cm = ecs->GetComponentManager(); //C
	SystemManager* sm = ecs->GetSystemManager(); //S

	// add systems
	Render2DSystem* renderSystem = sm->AddSystem<Render2DSystem>();
	PhysicsSystem* physicsSystem = sm->AddSystem<PhysicsSystem>();
	Collider2DSystem* colliderSystem = sm->AddSystem<Collider2DSystem>();

	Entity* e1 = AddPlayer(Vector2{ 300,0 }, Vector2{ 0,0.05 });
	CircleCollider* e1Collider = cm->AddComponent<CircleCollider>(e1->GetId());
	e1Collider->radius = 64;
	e1Collider->offset = Vector2{ 64, 64 };
	/*RectangleCollider* e1Collider = cm->AddComponent<RectangleCollider>(e1->GetId());
	e1Collider->width = 128;
	e1Collider->height = 80;
	e1Collider->offset = Vector2{ 0, 20 };*/

	Entity* e2 = AddPlayer(Vector2{ 0,300 }, Vector2{ 0.05,0 });
	/*RectangleCollider* e2Collider = cm->AddComponent<RectangleCollider>(e2->GetId());
	e2Collider->width = 128;
	e2Collider->height = 80;
	e2Collider->offset = Vector2{ 0, 20 };*/
	CircleCollider* e2Collider = cm->AddComponent<CircleCollider>(e2->GetId());
	e2Collider->radius = 64;
	e2Collider->offset = Vector2{ 64, 64 };

	// start
	ecs->Start();
	// game loop

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	SDL_Event Event;
	while (ecs->IsRunning())
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		while (SDL_PollEvent(&Event)) {}

		sm->Update(deltaTime);
		sm->Render(renderSystem->renderer);
	}

	delete ecs;

	return 0;
}
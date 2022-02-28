#include <iostream>

#include "ECS.h"
#include "Debug.h"

// systems
#include "PhysicsSystem.h"
#include "Render2DSystem.h"
#include "Collider2DSystem.h"

float RandomRange(int min,int max) {
	return rand() % (max - min + 1) + min;
}

double numEntities = 0;
Entity* AddPlayer() {
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
	playerTransform->position = Vector2{ RandomRange(0,800),RandomRange(0,600) };

	// add rigid body
	RigidBody2D* playerRB = cm->AddComponent<RigidBody2D>(player->GetId());
	playerRB->velocity = Vector2{ RandomRange(-100,100) / 100,RandomRange(-100,100) / 100 };
	playerRB->gravityScale = 0.000; // 05;

	// renderer
	SpriteRenderer2D* playerSprite = cm->AddComponent<SpriteRenderer2D>(player->GetId());
	playerSprite->src.x = 0;
	playerSprite->src.y = 0;
	playerSprite->src.w = 32;
	playerSprite->src.h = 32;
	playerSprite->dest.w = 32; // centered
	playerSprite->dest.h = 32; // centered
	playerSprite->surface = IMG_Load("assets/player.png");
	playerSprite->texture = SDL_CreateTextureFromSurface(renderSystem->renderer, playerSprite->surface);

	// collider
	if (true) {
		ScreenCollider* playerCollider = cm->AddComponent<ScreenCollider>(player->GetId());
	}
	if (false) {
		CircleCollider* playerCollider = cm->AddComponent<CircleCollider>(player->GetId());
		playerCollider->radius = 16;
		playerCollider->offset.x = 16;
		playerCollider->offset.y = 16;
	}

	++numEntities;
	return player;
}


int test() {
	Uint64 start; Uint64 finish;
	start = SDL_GetPerformanceCounter();
	for (int i = 0; i < 10000; i++) {
		typeid(CircleCollider);
	}
	finish = SDL_GetPerformanceCounter();
	std::cout << finish - start << std::endl;

	start = SDL_GetPerformanceCounter();
	for (int i = 0; i < 10000; i++) {
		typeid(CircleCollider).hash_code();
	}
	finish = SDL_GetPerformanceCounter();

	std::cout << finish - start << std::endl;
	return 0;
}

int main(int argc, char** argv) {
	return test();
	srand(time(NULL)); // Seed the time
	ECS* ecs = ECS::ECS_ENGINE();

	EntityManager* em = ecs->GetEntityManager(); //E
	ComponentManager* cm = ecs->GetComponentManager(); //C
	SystemManager* sm = ecs->GetSystemManager(); //S

	// add systems
	Render2DSystem* renderSystem = sm->AddSystem<Render2DSystem>();
	PhysicsSystem* physicsSystem = sm->AddSystem<PhysicsSystem>();
	Collider2DSystem* colliderSystem = sm->AddSystem<Collider2DSystem>();

	if (false) {
		// add boundary collider
		Entity* e1 = em->AddEntity();
		BoxCollider* e1c = cm->AddComponent<BoxCollider>(e1->GetId());
		e1c->width = 800;
		e1c->height = 600;
	}

	// start
	ecs->Start();
	// game loop

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;
	double frameRate = 0;
	double frameCount = 0;
	double startTime = SDL_GetPerformanceCounter();
	double runTime = 0;
	SDL_Event event;

	while (ecs->IsRunning())
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		runTime = NOW - startTime;
		frameRate = frameCount / (runTime / 10000000);
		std::cout << frameRate << ": " << numEntities << std::endl;

		AddPlayer();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				ecs->Stop();
			}
		}
		sm->Update(deltaTime);
		sm->Render(renderSystem->renderer);
		// render the framerate
		SDL_RenderPresent(renderSystem->renderer);
		++frameCount;
		if (numEntities >= 3000) {
			ecs->Stop();
		}
	}

	delete ecs;

	return 0;
}
#include <iostream>

#include "ECS.h"
#include "Input.h"
#include "Debug.h"
#include "Time.h"

// systems
#include "PhysicsSystem.h"
#include "Render2DSystem.h"
#include "Collider2DSystem.h"
#include "RouteCreatorSystem.h"
#include "TrainSystem.h"
#include "CursorSystem.h"
#include "Transform2D.h"
#include "Cursor.h"


int main(int argc, char** argv) {
	srand(time(NULL)); // Seed the time
	ECS* ecs = ECS::ECS_ENGINE();

	EntityManager* em = ecs->GetEntityManager(); //E
	ComponentManager* cm = ecs->GetComponentManager(); //C
	SystemManager* sm = ecs->GetSystemManager(); //S

	ecs->GetPrefabManager()->Load("prefabs.json");
	ecs->GetSystemManager()->Load("systems.json");
	ecs->GetSceneManager()->LoadScene("scenes.json","Gameplay");

	// start
	ecs->Start();
	// game loop

	Time* t = Time::Instance();
	while (ecs->IsRunning())
	{
		t->LAST = t->NOW;
		t->NOW = SDL_GetPerformanceCounter();
		t->deltaTime = (double)((t->NOW - t->LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		t->performanceRunTime = t->NOW - t->startTime;
		t->runTime = t->performanceRunTime / 10000; // run time in milliseconds
		t->frameRate = t->frameCount / (t->performanceRunTime / 10000000);

		Input::Instance()->Update();
		sm->Update(t->deltaTime);
		sm->Render(sm->GetSystem<Render2DSystem>()->renderer);

		++t->frameCount;
	}

	delete ecs;

	return 0;
}
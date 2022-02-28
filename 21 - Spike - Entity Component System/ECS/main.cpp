#include <iostream>

#include "ECS.h"

#include "ConstantVelocity2D.h"
#include "RigidBody2D.h"
#include "SpriteRenderer2D.h"
#include "Transform2D.h"

#include "PhysicsSystem.h"
#include "Render2DSystem.h"

void RunECSTests() {
	ECS* ecs = ECS::ECS_ENGINE();

	EntityManager* em = ecs->GetEntityManager(); //E
	ComponentManager* cm = ecs->GetComponentManager(); //C
	SystemManager* sm = ecs->GetSystemManager(); //S
	// --------------------- System Manager ---------------------

	Render2DSystem* rs = sm->GetSystem<Render2DSystem>(); // get a system that doesn't exist
	sm->AddSystem<PhysicsSystem>(); // add a system
	sm->AddSystem<Render2DSystem>(); // add another system
	rs = sm->GetSystem<Render2DSystem>(); // get a system that does exist
	sm->RemoveSystem<Render2DSystem>(); // delete a system that does exist
	sm->RemoveSystem<Render2DSystem>(); // delete a system that doesn't exist

	// --------------------- Entity Manager ---------------------

	Entity* entity1 = em->GetEntity(-1);// get an entity that doesn't exist
	entity1 = em->AddEntity(); // add an entity
	Entity* entity2 = em->AddEntity(); // add another entity
	entity1 = em->GetEntity(entity1->GetId());// get an entity that does exist
	em->RemoveEntity(entity2->GetId()); // remove an entity that does exist
	entity2 = em->GetEntity(entity2->GetId());// get an entity that does exist
	em->RemoveEntity(-1); // remove an entity that doesn't exist

	// --------------------- Component Manager ---------------------
	cm->AddComponent<ConstantVelocity2D>(entity1->GetId()); // add a component to an entity
	cm->AddComponent<RigidBody2D>(entity1->GetId()); // add a component to an entity
	cm->AddComponent<SpriteRenderer2D>(entity1->GetId()); // add a component to an entity
	cm->AddComponent<Transform2D>(entity1->GetId()); // add a component to an entity
	ConstantVelocity2D* cv2d1 = cm->GetComponent<ConstantVelocity2D>(entity1->GetId()); // get component of an entity

	entity2 = em->AddEntity();
	cm->AddComponent<ConstantVelocity2D>(entity2->GetId()); // add a component to an entity
	cm->AddComponent<RigidBody2D>(entity2->GetId()); // add a component to an entity
	cm->AddComponent<SpriteRenderer2D>(entity2->GetId()); // add a component to an entity
	cm->AddComponent<Transform2D>(entity2->GetId()); // add a component to an entity
	ConstantVelocity2D* cv2d2 = cm->GetComponent<ConstantVelocity2D>(entity2->GetId()); // get component of an entity

	bool doesntMatch = cv2d1 != cv2d2; // make sure the components don't match because there are 2 instances
	std::vector<ConstantVelocity2D*> cv2ds = cm->GetComponents<ConstantVelocity2D>(); // get all constant velocity components, regardless of their entity
	bool twoFound = cv2ds.size() == 2; // both instances created were found

	cm->RemoveComponent<ConstantVelocity2D>(entity2->GetId()); //remove one of the components
	cm->RemoveComponent<ConstantVelocity2D>(-1); //remove a component on entity that doesn't exist
	cv2ds = cm->GetComponents<ConstantVelocity2D>(); // get all constant velocity components, regardless of their entity
	bool oneFound = cv2ds.size() == 1; // both instances created were found


	cm->AddComponent<ConstantVelocity2D>(entity1->GetId()); // add a second of same component to an entity
	cv2ds = cm->GetComponents<ConstantVelocity2D>(entity1->GetId());// get multiple component of type t for one entity
	twoFound = cv2ds.size() == 2; // both instances created were found
}

int main(int argc, char** argv) {
	ECS* ecs = ECS::ECS_ENGINE();

	EntityManager* em = ecs->GetEntityManager(); //E
	ComponentManager* cm = ecs->GetComponentManager(); //C
	SystemManager* sm = ecs->GetSystemManager(); //S

	// add systems
	Render2DSystem* renderSystem = sm->AddSystem<Render2DSystem>();
	PhysicsSystem* physicsSystem = sm->AddSystem<PhysicsSystem>();

	// add player
	Entity* player = em->AddEntity();
	Transform2D* playerTransform = cm->AddComponent<Transform2D>(player->GetId());
	ConstantVelocity2D* playerConstantVelocity = cm->AddComponent<ConstantVelocity2D>(player->GetId());
	SpriteRenderer2D* playerSprite = cm->AddComponent<SpriteRenderer2D>(player->GetId());

	playerSprite->surface = IMG_Load("assets/player.png");
	playerSprite->texture = SDL_CreateTextureFromSurface(renderSystem->renderer, playerSprite->surface);

	playerSprite->src.x = 0;
	playerSprite->src.y = 0;
	playerSprite->src.w = 256;
	playerSprite->src.h = 256;
	playerSprite->dest.w = 128; // centered
	playerSprite->dest.h = 128; // centered

	playerTransform->position.x = 0;
	playerTransform->position.y = 600;

	playerConstantVelocity->velocity.x = 0.01;
	playerConstantVelocity->velocity.y = -0.01;

	// start
	ecs->Start();
	// game loop
	while (ecs->IsRunning()) {
		sm->Update(cm);
		sm->Render(cm);
	}

	delete ecs;

	return 0;
}

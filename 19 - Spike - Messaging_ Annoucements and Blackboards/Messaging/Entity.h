#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "Message.h"
#include "PostOffice.h"

typedef std::vector<Message*> Inbox;

class Entity {
public:
	Inbox inbox;
	std::string id;
	PostOffice* po = nullptr;
	
	virtual void ProcessInbox() = 0;
};

class Player : public Entity {
public:
	void Entity::ProcessInbox() override;
};

class Key : public Entity {
public:
	void Entity::ProcessInbox() override;
};


enum class DoorState {
	LOCKED,
	UNLOCKED
};
class Door : public Entity {
public:
	Key* key = nullptr;
	DoorState state;
	void Entity::ProcessInbox() override;
};
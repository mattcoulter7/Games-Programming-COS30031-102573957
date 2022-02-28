#pragma once
#include <iostream>
#include <vector>
#include <array>
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
	std::array<int,2> position;
	void Entity::ProcessInbox() override;
};
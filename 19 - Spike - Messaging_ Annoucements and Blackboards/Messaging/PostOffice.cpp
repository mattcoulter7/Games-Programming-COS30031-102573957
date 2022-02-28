#pragma once
#include <vector>

#include "PostOffice.h"
#include "Entity.h"

void PostOffice::RegisterEntity(Entity* entity) {
	_entities.push_back(entity);
	entity->po = this;
}
void PostOffice::Send(Message* msg) {
	Entity* recipient = FindRecipient(msg->to);
	Deliver(msg, recipient);
}
void PostOffice::Forward(Message* msg, std::string recipientid) {
	Entity* recipient = FindRecipient(recipientid);
	Deliver(msg, recipient);
}
void PostOffice::Reply(Message* receivedMsg, Message* msg) {
	Entity* recipient = receivedMsg->from;
	msg->lastMessage = receivedMsg;
	Deliver(msg, recipient);
}

Entity* PostOffice::FindRecipient(std::string id) {
	Entity* recipient = nullptr;
	for (Entity* entity : _entities) {
		if (entity->id == id) {
			recipient = entity;
		}
	}
	return recipient;
}
void PostOffice::Deliver(Message* msg, Entity* entity) {
	// send failure if receipient is not specified
	if (entity == nullptr) {
		ReturnToSender(msg);
	}
	else {
		// place in their inbox
		entity->inbox.push_back(msg);
	}
}
void PostOffice::ReturnToSender(Message* msg) {
	// try send a message back to sender failure to deliver
	Entity* sender = msg->from;
	if (sender != nullptr) {
		sender->inbox.push_back(new Message{
			nullptr,
			sender->id,
			MessageType::ERROR,
			"Error: Recipient " + msg->to + " does not exist.",
			MessagePriority::HIGH,
			msg
		});
	}
}
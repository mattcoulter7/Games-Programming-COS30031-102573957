#pragma once
#include <vector>

#include "PostOffice.h"
#include "Entity.h"

void PostOffice::RegisterEntity(Entity* entity) {
	_entities.push_back(entity);
	entity->po = this;
}
void PostOffice::Send(Message* msg) {
	std::vector<Entity*> recipients;
	if (msg->to == "all") {
		recipients = _entities;
	}
	else {
		recipients = FindRecipient(msg->to);
	}
	Deliver(msg, recipients);
}
void PostOffice::Forward(Message* msg, std::string recipientid) {
	std::vector<Entity*> recipients = FindRecipient(recipientid);
	Deliver(msg, recipients);
}
void PostOffice::Reply(Message* receivedMsg, Message* msg) {
	Entity* recipient = receivedMsg->from;
	std::vector<Entity*> from{ recipient };
	msg->lastMessage = receivedMsg;
	Deliver(msg, from);
}

std::vector<Entity*> PostOffice::FindRecipient(std::string id) {
	std::vector<Entity*> recipients;
	for (Entity* entity 
		if (entity->id == id) {
			recipients.push_back(entity);
		}
	}
	return recipients;
}
void PostOffice::Deliver(Message* msg, std::vector<Entity*> entities) {
	// send failure if receipient is not specified
	for (auto entity 
		if (entity == nullptr) {
			ReturnToSender(msg);
		}
		else {
			// place in their inbox
			entity->inbox.push_back(msg);
		}
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
			"Error
			MessagePriority::HIGH,
			msg
		});
	}
}
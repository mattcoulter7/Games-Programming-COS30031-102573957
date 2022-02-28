#pragma once
#include <vector>
#include <string>

class Entity;
class Message;

class PostOffice {
public:
	void RegisterEntity(Entity* entity);
	void Send(Message* msg);
	void Forward(Message* msg, std::string recipientid);
	void Reply(Message* receivedMsg, Message* msg);
private:
	std::vector<Entity*> FindRecipient(std::string id);
	void Deliver(Message* msg, std::vector<Entity*> entity);
	void ReturnToSender(Message* msg);

	std::vector<Entity*> _entities; // need to have knowledge of entities to handle deliveries
};
#pragma once
#include <string>
class Entity;

enum class MessageType {
	DEFAULT,
	ATTACK,
	ERROR
};

enum class MessagePriority {
	HIGH,
	MEDIUM,
	LOW
};

struct Message {
	Entity* from;
	std::string to;
	MessageType type;
	std::string data;
	MessagePriority priority;
	Message* lastMessage; // message that was responded to
};
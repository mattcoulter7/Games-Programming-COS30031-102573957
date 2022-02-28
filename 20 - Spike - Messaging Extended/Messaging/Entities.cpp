#include "Entity.h"

void Player::ProcessInbox() {
	while (inbox.size() > 0) {
		Message* msg = inbox.at(0);
		std::string from = msg->from != nullptr ? msg->from->id : "no-reply";
		std::cout << "from: " << from << ", to: " << msg->to << " \"" << msg->data << "\"" << std::endl;

		if (msg->type == MessageType::ATTACK) {
			po->Reply(msg, new Message{
				this,
				from,
				MessageType::DEFAULT,
				"You have dealt 50 damage to me.",
				MessagePriority::MEDIUM,
			});
		}

		inbox.erase(inbox.begin());
	}
}
#include "Entity.h"

void Key::ProcessInbox() {
	while (inbox.size() > 0) {
		Message* msg = inbox.at(0);
		std::string from = msg->from != nullptr ? msg->from->id : "no-reply";
		std::cout << "from: " << from << ", to: " << msg->to << " \"" << msg->data << "\"" << std::endl;
		if (msg->data == "unlock door B") { // command pattern would be good in real world
			po->Reply(msg,new Message{
				this,
				from,
				MessageType::DEFAULT,
				"unlock",
				MessagePriority::HIGH,
			});
		}
		inbox.erase(inbox.begin());
	}
}
void Door::ProcessInbox() {
	while (inbox.size() > 0) {
		Message* msg = inbox.at(0);
		std::string from = msg->from != nullptr ? msg->from->id : "no-reply";
		std::cout << "from: " << from << ", to: " << msg->to << " \"" << msg->data << "\""<< std::endl;
		if (msg->data == "unlock") {
			if (msg->from == key) {
				state = DoorState::UNLOCKED;
				po->Reply(msg,new Message{
					this,
					from,
					MessageType::DEFAULT,
					"door has been unlocked",
					MessagePriority::HIGH
				});
			}
			else {
				state = DoorState::UNLOCKED;
				po->Reply(msg,new Message{
					this,
					"A",
					MessageType::DEFAULT,
					"incorrect key for door",
					MessagePriority::HIGH,
				});
			}
		}
		inbox.erase(inbox.begin());
	}
}
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
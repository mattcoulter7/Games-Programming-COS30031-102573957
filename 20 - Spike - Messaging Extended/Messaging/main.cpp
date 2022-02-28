#include <iostream>

#include "PostOffice.h"
#include "Entity.h"
#include "Message.h"

int main() {
	// create the elf
	Player* player = new Player();
	player->id = "A";

	// create the orc
	Player* enemy1 = new Player();
	enemy1->id = "B";
	Player* enemy2 = new Player();
	enemy2->id = "C";
	Player* enemy3 = new Player();
	enemy3->id = "D";
	Player* enemy4 = new Player();
	enemy4->id = "E";
	Player* enemy5 = new Player();
	enemy5->id = "F";

	// create po and register both entities
	PostOffice* po = new PostOffice();
	po->RegisterEntity(enemy1);
	po->RegisterEntity(enemy2);
	po->RegisterEntity(enemy3);
	po->RegisterEntity(enemy4);
	po->RegisterEntity(enemy5);

	// player telling key to try opening door
	po->Send(new Message{
		player,
		"all",
		MessageType::ATTACK,
		"sword at mid-height",
		MessagePriority::HIGH,
		nullptr, // message that was responded to
	});

	enemy1->ProcessInbox();
	enemy2->ProcessInbox();
	enemy3->ProcessInbox();
	enemy4->ProcessInbox();
	enemy5->ProcessInbox();

	// seeing if anyone was hit
	player->ProcessInbox();

	delete player;
	delete enemy1;
	delete enemy2;
	delete enemy3;
	delete enemy4;
	delete enemy5;
	delete po;

	return 0;
}
#include <iostream>

#include "PostOffice.h"
#include "Entity.h"
#include "Message.h"


/* ----------------- A to B to change state (simple message, no extra data) ----------------- */

/*
A player uses a key (A) is on a locked door (B), so the key sends a message to the door to “unlock”.
{ from: player, to: A, message: “unlock took B” } // door identified in the message string? Ok …
{ from: A, to: B, message: “unlock” } // should this work? Key match? Hmm…
*/
void example3() {
	Player* player = new Player();
	player->id = "player1";

	Key* key = new Key();
	key->id = "A";

	Door* door = new Door();
	door->id = "B";
	door->key = key;
	door->state = DoorState::LOCKED;

	PostOffice* po = new PostOffice();
	po->RegisterEntity(key);
	po->RegisterEntity(door);
	po->RegisterEntity(player);

	// player telling key to try opening door
	po->Send(new Message{
		player,
		"A",
		MessageType::DEFAULT,
		"unlock door B",
		MessagePriority::HIGH,
		nullptr, // message that was responded to
	}); // player to a
	key->ProcessInbox(); // key processes players message, and tells door to open
	door->ProcessInbox(); // door reads the keys message and attempts to unlock door if there is a key match
	key->ProcessInbox(); // door tells key whether the door opened or not

	// clean up
	delete key;
	delete door;
	delete player;
	delete po;
}

/* ----------------- A to B with data. (Simple message as “kind”/type, but with - say - an extra data part as … string or pointer) ----------------- */
/*
Elf character (A) is doing a mid-height sword attack to an orc (B). So
{ from: A, to: B, kind: “attack”, data: ”sword at mid-height” }
*/
void example5() {
	// create the elf
	Player* elf = new Player();
	elf->id = "A";

	// create the orc
	Player* orc = new Player();
	orc->id = "B";

	// create po and register both entities
	PostOffice* po = new PostOffice();
	po->RegisterEntity(elf);
	po->RegisterEntity(orc);

	// player telling key to try opening door
	po->Send(new Message{
		elf,
		"B",
		MessageType::ATTACK,
		"sword at mid-height",
		MessagePriority::HIGH,
		nullptr, // message that was responded to
	});

	elf->ProcessInbox();
	orc->ProcessInbox();
	elf->ProcessInbox();

	delete elf;
	delete orc;
	delete po;
}

/* ----------------- A to B, then B to A with response ----------------- */

/*
In a soccer game, the AI player A (also known by int id=3) has the ball and wants to kick the ball to the best
positioned team mate. It asks the map (B, known by id=12) “who is best to kick to?” (using an enum). The
map figures this out when it can (it’s rather busy) then sends a message back to player (id=3) with a list of
potential support players, each with int id numbers.
{ from: 3, to: 12, message: BEST_KICK_LIST, data: [] }
{ from: 12, to: 3, message: BEST_KICK_LIST_RESULT, data: [4,1,3,9] }
*/
void example7() {

}


int main() {
	if (false) {
		example3();
	}
	if (true) {
		example5();
	}
	if (false) {
		example7();
	}
	return 0;
}
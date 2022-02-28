#include "Player.h"

Player::Player() {
	steps = 0;
	inventory = new Inventory();
	location = 0;
}

void Player::SetLocation(int _location) {
	location = _location;
}

Inventory* Player::GetInventory() {
	return inventory;
};
int Player::GetLocation() { return location; };
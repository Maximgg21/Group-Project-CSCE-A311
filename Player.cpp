#include "Player.h"

string Player::getName()
{
	return name;
}

void Player::move(int new_x, int new_y)
{
	this->x = new_x;
	this->y = new_y;
}

void Player::attack(Player& opponent)
{
	opponent.HP--;
}

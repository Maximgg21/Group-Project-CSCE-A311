#include "Player.h"

Player::Player(string name, int x, int y) : name(name), x(x), y(y) , HP(20), ATK(3), MS(1), gold(0) {

};

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


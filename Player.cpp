#include "Player.h"

Player::Player(string name, int x, int y) : name(name), x(x), y(y) , HP(20) {};

Player::Player() : name(""), x(0), y(0), HP(20) {};

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

void Player::collect()
{
}


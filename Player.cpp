#include "Player.h"
#include <iostream>

Player::Player() : name("0"), x(0), y(0), HP(20), ATK(3), MS(1), gold(7), cpu(true)
{
}

Player::Player(string name, int x, int y) : name(name), x(x), y(y) , HP(20), ATK(3), MS(1), gold(0), cpu(true) {

};

string Player::getName()
{
	return name;
}

int Player::getGold()
{
	return gold;
}

void Player::setGold(int g)
{
	gold = g;
}

int Player::getMS()
{
	return MS;
}

void Player::setMS(int m)
{
	MS = m;
}

int Player::getATK()
{
	return ATK;
}

void Player::setATK(int a)
{
	ATK = a;
}

int Player::getHP()
{
	return HP;
}

void Player::setHP(int h)
{
	HP = h;
}

bool Player::getCpu()
{
	return cpu;
}

void Player::setCpu(bool b)
{
	cpu = b;
}

void Player::move(int new_x, int new_y)
{
	this->x = new_x;
	this->y = new_y;
}

void Player::attack(Player* opponent)
{
	opponent->HP -= ATK;
}

void Player::view_stats()
{
	cout << "----------" << endl;
	cout << "HP  : " << HP	<< endl;
	cout << "MS  : " << MS	<< endl;
	cout << "ATK : " << ATK << endl;
	cout << "----------" << endl;


}



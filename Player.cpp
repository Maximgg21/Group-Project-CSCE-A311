#include "Player.h"
#include <iostream>

Player::Player() : name("0"), x(0), y(0), HP(20), ATK(3), MS(1), gold(7)
{
}

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
	opponent.HP -= ATK;
}

void Player::upgrade(map<string, map<string, int>> store)
{
	/*Opens the store and lists the items that a player can buy to upgrade their stats*/
	cout << "You have " << gold << " gold" << endl;
	cout << "What would you like to buy? (Type 'exit' to leave)" << endl;

	for (const auto& item : store) {		// List the items in the store
		cout << '[' << item.first << ']' << endl;
	}

	string order;
	while (getline(cin, order)) {		// Get an input (order)
		if (order == "exit") cout << "You left the store" << endl; return;

		if (store.find(order) == store.end()) {
			cout << "There is no such item in the store" << endl;
		}
		else if (gold < store[order]["price"]) {
			cout << "You don't have enough gold to buy this item" << endl;
		}
		else {
			break;
		}
	}

	HP += store[order]["health"];	// Add stats for the item ordered
	ATK += store[order]["attack"];	// If store[order] doesn't have such attributes, it adds 0
	MS += store[order]["speed"];
	
	cout << "You bought the item. Your stats now are: " << "HP = " << HP << ", ATK = " << ATK << ", MS = " << MS << endl;
}


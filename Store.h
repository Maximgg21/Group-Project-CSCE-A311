#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Player.h"
struct Item
{
	std::string name;
	std::string description; 
	int type; // 1 for ATK buff, 2 for Health, 3 for MS
	int price; // How much the item costs
	int buff; // How much the stat will be modified
	shared_ptr<Item> next;
	shared_ptr<Item> prev;
};

class Store
{
private:
	shared_ptr<Item> head;
	shared_ptr<Item> tail;
	void purchaseItem(shared_ptr<Item> i, Player* u); // Used by accessStore. Applies buff, removes gold, and if neccesary, deletes item from store.
public:
	Store(); // Constructs the linked list using a vector holding Item objects.
	bool accessStore(Player* user, string item = ""); // Opens the store menu.
	shared_ptr<Item> findItem(std::string n); // Used by accessStore and World.cpp - Returns pointer to desired item to have easily accessable.
};
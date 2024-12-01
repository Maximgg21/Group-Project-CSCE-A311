#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <queue>
#include "Player.h"
#include "Store.h"
#include "stdlib.h"

using namespace std;

struct Cell {
	int gold;
	shared_ptr<Item> cellItem; // If the cell contains an item this will contain a pointer to that item in the worldStore.
	string display;		// How it is displayed on the map
	Player* occupied;

	Cell() : gold(0), display("  "), cellItem(nullptr), occupied(nullptr) {};
	Cell(int g, shared_ptr<Item> i, string d, Player* o) : gold(g), cellItem(i), display(d), occupied(o) {};
};

class World
{
public:
	World();
	Store* worldStore; // Added for regenerateWorld function to work with placing potions.
	void placePlayers(int playerCount); // Places given amount of players in the world
	void print(); // Prints the world for the user (This should be a private function later used inside play() )
	void play();	// Plays the game
private:
	int turn;
	void regenerateWorld(int goldAmount, int potionsAmount, Store* s);	// Generates items in the world
	pair<int, int> randomEmptyTile();	// Gets coordinates x, y of an empty position in the world
	vector<vector<Cell>> world;		// The map

	queue<Player*> playerTurns;		// Store players to determine turns

	void attack_range(Player* p);				// Determines who the player can attack
	void move_range(Player* p);					// Handles the event of a player moving
	void item_collection(Player* p);
};


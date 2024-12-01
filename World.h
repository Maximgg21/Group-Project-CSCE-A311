#pragma once
#include <vector>
#include <string>
#include <queue>
#include "Player.h"
#include "Store.h"

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
	~World();
	void play();	// Plays the game
private:
	Store* worldStore; // Added for regenerateWorld function to work with placing potions.
	vector<vector<Cell>> world;		// The map
	queue<Player*> playerTurns;		// Store players to determine turns
	bool playWithBots;
	void print(); // Prints the world for the user
	void placePlayers(); // Places given amount of players in the world
	void regenerateWorld(int goldAmount, int potionsAmount, Store* s);	// Generates items in the world
	pair<int, int> randomEmptyTile();	// Gets coordinates x, y of an empty position in the world
	void computer_turn(Player* p); // Automates turn for non played players
	bool attack_range(Player* p);				// Determines who the player can attack
	bool move_range(Player* p);					// Handles the event of a player moving
	void item_collection(Player* p);
};


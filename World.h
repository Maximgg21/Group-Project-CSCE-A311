#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <queue>
#include "Player.h"
#include "stdlib.h"

using namespace std;

struct Cell {
	int gold;
	string storeKey;	// Key for the item in store
	string display;		// How it is displayed on the map
	Player* occupied;

	Cell() : gold(0), storeKey(""), display("  "), occupied(nullptr) {};
	Cell(int g, string sk, string d, Player* o) : gold(g), storeKey(sk), display(d), occupied(o) {};
};

class World
{
public:
	World();
	void placePlayers(int playerCount); // Places given amount of players in the world
	void print(); // Prints the world for the user (This should be a private function later used inside play() )
	void play();	// Plays the game
private:
	int turn;
	void regenerateWorld(int goldAmount, int potionsAmount);	// Generates items in the world
	pair<int, int> randomEmptyTile();	// Gets coordinates x, y of an empty position in the world
	vector<vector<Cell>> world;		// The map
	map<string, map<string, int>> store;		// Items and their stats
	unordered_map<string, string> storeDisplay;		// Items and their display
	queue<Player*> playerTurns;
	void initializeStore();

};


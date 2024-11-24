#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Player.h"

using namespace std;

struct Cell {
	int gold;
	string storeKey;	// Key for the item in store
	string display;
	Player* occupied;

	Cell() : gold(0), storeKey(""), display("  "), occupied(nullptr) {};
	Cell(int g, string sk, string d, Player* o) : gold(g), storeKey(sk), display(d), occupied(o) {};
};

class World
{
public:
	World();
	void placePlayers(int playerCount); // Places given amount of players in the world
	void print(); // Prints the world for the user
private:
	void generateWorld();	// Generates items, obstacles and gold in the world
	pair<int, int> randomEmptyTile();	// Gets coordinates x, y of an empty position in the world
	vector<vector<Cell>> world;
	unordered_map<string, unordered_map<string, int > > store;
	unordered_map<string, string> storeDisplay;
};


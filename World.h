#pragma once
#include <vector>
#include <string>
#include "Player.h"

using namespace std;

struct Cell {
	int resource;
	string display;
	Player* occupied;


	Cell(int r = 0, string d = "", Player* o = nullptr) : resource(r), display(d), occupied(o) {};
};

class World
{
public:
	World();
	void placePlayers(int playerCount); // Places given amount of players in the world
	void print(); // Prints the world for the user
private:
	vector<vector<Cell>> world; 
};


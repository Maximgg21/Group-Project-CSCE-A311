#include "World.h"
#include <iostream>

const int SIZE = 15;

World::World() : world(SIZE, vector<Cell>(SIZE, Cell()))
{
	srand(time(NULL));

	store["katana"] = { {"price", 10}, { "attack", 10 }, {"range", 1}};
	store["spear"] = { {"price", 10}, {"attack", 7}, {"range", 2} };
	store["bow"] = { {"price", 10}, {"attack", 5}, {"range", 3} };

	storeDisplay["katana"] = "Ka";
	storeDisplay["spear"] = "Sp";
	storeDisplay["bow"] = "Bo";

	generateWorld();
}



void World::placePlayers(int playerCount)
{
	for (int i = 0; i < playerCount; i++) {
		pair<int, int> result = randomEmptyTile();
		int x = result.first;
		int y = result.second;

		world[x][y].occupied = new Player(to_string(i + 1), x, y);
		world[x][y].display = 'P' + world[x][y].occupied->getName();
	}
}

void World::print()
{
	// Print the map
	for (int i = 0; i < SIZE * 3 + 1; i++) {
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < SIZE; i++) {
		cout << '|';
		for (int j = 0; j < SIZE; j++) {
			cout << world[i][j].display << '|';
		}
		cout << endl;
	}

	for (int i = 0; i < SIZE * 3 + 1; i++) {
		cout << "-";
	}
	cout << endl;
}

void World::generateWorld()
{
	int storeSize = storeDisplay.size();

	for (int i = 0; i < 3; i++) {		// Generate weapons from store
		pair<int, int> result = randomEmptyTile();
		int x = result.first;
		int y = result.second;
		
		int randIndex = rand() % storeSize;		// Select a random item from the store
		auto it = storeDisplay.begin();
		advance(it, randIndex);

		world[x][y].storeKey = it->first;
		world[x][y].display = it->second;
	}

	for (int i = 0; i < 3; i++) {
		pair<int, int> result = randomEmptyTile();
		int x = result.first;
		int y = result.second;
		
		int randomGold = rand() % 10;

		world[x][y].gold = randomGold;
		world[x][y].display = 'G' + to_string(randomGold);
	}
}

pair<int, int> World::randomEmptyTile()
{
	while (true) {
		int x = rand() % SIZE, y = rand() % SIZE;

		if (world[x][y].display == "  ")
		{
			return { x, y };
		}
	}
}

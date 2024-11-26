#include "World.h"
#include <iostream>

const int SIZE = 15;	// World size

World::World() : turn(0), world(SIZE, vector<Cell>(SIZE, Cell()))
{
	srand(time(NULL));

	cout << "P - player" << endl;
	cout << "G - gold" << endl;
	cout << "H - health potion" << endl;
	cout << "S - speed potion" << endl;
	cout << "P - power potion" << endl;

	initializeStore();		// Initialization of the items in the store

	regenerateWorld(7, 3);	// First generation of the world
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

void World::regenerateWorld(int goldAmount, int potionsAmount)
{
	int storeSize = storeDisplay.size();

	for (int i = 0; i < potionsAmount; i++) {		// Generate potions from the store
		pair<int, int> result = randomEmptyTile();
		int x = result.first;
		int y = result.second;

		int randIndex = rand() % storeSize;		// Select a random item from the store
		auto it = storeDisplay.begin();
		advance(it, randIndex);

		world[x][y].storeKey = it->first;
		world[x][y].display = it->second;
	}

	for (int i = 0; i < goldAmount; i++) {				// Generate gold
		pair<int, int> result = randomEmptyTile();
		int x = result.first;
		int y = result.second;

		int randomGold = rand() % 9 + 1;

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

void World::initializeStore()
{
	store["power potion 1"] = { {"price", 5}, { "attack", 1 } };
	store["power potion 2"] = { {"price", 7}, { "attack", 2 } };
	store["power potion 3"] = { {"price", 10}, { "attack", 3 } };

	store["speed potion 1"] = { {"price", 5}, { "speed", 1 } };
	store["speed potion 2"] = { {"price", 7}, { "speed", 2 } };
	store["speed potion 3"] = { {"price", 10}, { "speed", 3 } };

	store["health potion 1"] = { {"price", 5}, { "health", 3 } };
	store["health potion 2"] = { {"price", 7}, { "health", 6 } };
	store["health potion 3"] = { {"price", 10}, { "health", 10 } };

	storeDisplay["power potion 1"] = "P1";
	storeDisplay["power potion 2"] = "P2";
	storeDisplay["power potion 3"] = "P3";

	storeDisplay["speed potion 1"] = "S1";
	storeDisplay["speed potion 2"] = "S2";
	storeDisplay["speed potion 3"] = "S3";

	storeDisplay["health potion 1"] = "H1";
	storeDisplay["health potion 2"] = "H2";
	storeDisplay["health potion 3"] = "H3";
}

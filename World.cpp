#include "World.h"
#include <iostream>

const int SIZE = 15;	// World size

World::World() : turn(0), world(SIZE, vector<Cell>(SIZE, Cell()))
{
	srand(time(NULL));

	cout << "P - player" << endl;
	cout << "G - gold" << endl;
	cout << "HP - health potion" << endl;
	cout << "SP - speed potion" << endl;
	cout << "PP - power potion" << endl;

	worldStore = new Store;

	regenerateWorld(7, 3, worldStore);	// First generation of the world
}

void World::placePlayers(int playerCount)
{
	/* Places players on the map */
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

void World::play()
{
}

void World::regenerateWorld(int goldAmount, int potionsAmount, Store* s)
{
	/* Generates new items on the map */
	for (int i = 0; i < potionsAmount; i++) {		// Generate potions from the store
		pair<int, int> result = randomEmptyTile();
		vector<string> spawnPotions = { "Small Power Potion", "Small Health Potion", "Small Speed Potion" };
		int x = result.first;
		int y = result.second;

		int randIndex = rand() % spawnPotions.size();		// Select a random item from the store
		world[x][y].cellItem = s->findItem(spawnPotions[randIndex]);
		switch (randIndex) {
		case 0:
			world[x][y].display = "PP";
			break;
		case 1:
			world[x][y].display = "HP";
			break;
		case 2:
			world[x][y].display = "SP";
			break;
		default:
			break;
		}
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
	/* Gets a random empty tile on the map */
	while (true) {
		int x = rand() % SIZE, y = rand() % SIZE;

		if (world[x][y].display == "  ")
		{
			return { x, y };
		}
	}
}

#include "World.h"
#include <iostream>

const int SIZE = 15;

World::World() : world(SIZE, vector<Cell>(SIZE, Cell()))
{
	srand(time(NULL));
	



	store["katana"] = { {"price", 10}, { "attack", 10 }, {"range", 1}};
	store["spear"] = { {"price", 10}, {"attack", 7}, {"range", 2} };
	store["bow"] = { {"price", 10}, {"attack", 5}, {"range", 3} };

	displayStore["katana"] = "Ka";
	displayStore["spear"] = "Sp";
	displayStore["bow"] = "Bo";

}



void World::placePlayers(int playerCount)
{
	for (int i = 0; i < playerCount; i++) {
		int x = rand() % SIZE, y = rand() % SIZE;

		if (world[x][y].occupied != nullptr) {
			i--;
			break;
		}

		world[x][y].occupied = new Player(to_string(i + 1), x, y);
		world[x][y].display = 'P' + world[x][y].occupied->getName();
	}
}

void World::print()
{
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
	
}

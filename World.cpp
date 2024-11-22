#include "World.h"
#include <iostream>

World::World()
{
	srand(time(NULL));
	world.resize(10, std::vector<Cell>(10, Cell(1, "X", nullptr)));
}

void World::placePlayers(int playerCount)
{
	for (int i = 0; i < playerCount; i++) {
		int x = rand() % 10, y = rand() % 10;
		if (world[x][y].occupied != nullptr) {
			i--;
			break;
		}
		world[x][y].occupied = new Player(std::to_string(i + 1), x, y);
		world[x][y].display = world[x][y].occupied->getName();
	}
}

void World::print()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << world[i][j].display << " ";
		}
		std::cout << std::endl;
	}
}

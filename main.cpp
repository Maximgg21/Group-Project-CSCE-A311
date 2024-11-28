#include <iostream>
#include "World.h"

using namespace std;

int main() {
	World demoWorld;

	/*int playerCount;
	cout << "How many players would you like? (Max 9)" << endl;
	cin >> playerCount;*/

	demoWorld.placePlayers(3);

	demoWorld.print();
	map<string, map<string, int>> store;		// Items and their stats

	store["power potion 1"] = { {"price", 5}, { "attack", 1 } };
	store["power potion 2"] = { {"price", 7}, { "attack", 2 } };
	store["power potion 3"] = { {"price", 10}, { "attack", 3 } };

	store["speed potion 1"] = { {"price", 10}, { "speed", 1 } };
	store["speed potion 2"] = { {"price", 14}, { "speed", 2 } };
	store["speed potion 3"] = { {"price", 20}, { "speed", 3 } };

	store["health potion 1"] = { {"price", 5}, { "health", 3 } };
	store["health potion 2"] = { {"price", 7}, { "health", 6 } };
	store["health potion 3"] = { {"price", 10}, { "health", 10 } };

	Player player;
	player.upgrade(store);
}
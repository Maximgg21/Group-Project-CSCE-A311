#include <iostream>
#include "World.h"

using namespace std;

int main() {
	World demoWorld;

	/*int playerCount;
	cout << "How many players would you like? (Max 9)" << endl;
	cin >> playerCount;*/

	demoWorld.placePlayers(3);
	demoWorld.play();



	/* Tests */
	demoWorld.print();

	map<string, map<string, int>> store;		// Items and their stats

	store["power potion 1"] = { {"price", 5}, { "attack", 1 } };
	store["power potion 2"] = { {"price", 7}, { "attack", 2 } };
	store["power potion 3"] = { {"price", 10}, { "attack", 3 } };

	Player player;
	player.upgrade(store);
}
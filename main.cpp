#include <iostream>
#include "World.h"
#include "Store.h"

using namespace std;

int main() {
	World demoWorld;

	/*int playerCount;
	cout << "How many players would you like? (Max 9)" << endl;
	cin >> playerCount;*/

	demoWorld.placePlayers(1);
	demoWorld.play();


	/* Test

	demoWorld.print();
	Store playerStore;

	Player player;

	cout << "HP = " << player.getHP() << ", ATK = " << player.getATK() << ", MS = " << player.getMS() << endl;
	playerStore.accessStore(player);
	*/
	return 0;
}
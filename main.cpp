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
}
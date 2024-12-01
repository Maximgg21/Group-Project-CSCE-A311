#include <iostream>
#include "World.h"
#include "Store.h"
#include "stdlib.h"

using namespace std;

int main() {
	srand(time(NULL));

	World demoWorld;

	demoWorld.play();

	return 0;
}
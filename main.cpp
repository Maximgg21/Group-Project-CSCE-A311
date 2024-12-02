#include <iostream>
#include "World.h"
#include "Store.h"
#include "stdlib.h"
#include <Windows.h>

using namespace std;

int main() {
	// Enable ANSI escape codes in Windows console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	srand(time(NULL));

	World demoWorld;

	demoWorld.play();

	return 0;
}
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
	std::cout << "\033[1;31m" << "This is red text on Windows!" << "\033[0m" << std::endl;

	srand(time(NULL));

	World demoWorld;

	demoWorld.play();

	return 0;
}
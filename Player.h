#pragma once
#include <string>
using namespace std;

class Player
{
public:
	Player(string n = "", int x = 0, int y = 0, int h = 20, int a = 5, int r = 0) : name(n), x(x), y(y), HP(h), attack(a), resources(r) {};
	string getName();
private:
	int x, y, HP, attack, resources;
	string name;
};


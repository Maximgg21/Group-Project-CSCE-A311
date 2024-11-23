#pragma once
#include <string>
using namespace std;

class Player
{
public:
	Player(string n = "", int x = 0, int y = 0, int h = 20, int r = 0) : name(n), x(x), y(y), HP(h), resources(r) {};
	string getName();
	void move(int new_x, int new_y);
	void attack(Player& opponent);



private:
	int x, y, HP, resources;
	string name;
};


#pragma once
#include <map>
#include <string>
using namespace std;

class Player
{
public:
	Player(string n, int x, int y);
	Player();
	string getName();
	void move(int new_x, int new_y);
	void attack(Player& opponent);
	void collect();



private:
	int x, y, HP;
	string name;
};


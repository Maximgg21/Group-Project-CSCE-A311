#pragma once
#include <map>
#include <string>
using namespace std;

class Player
{
public:
	Player(string n, int x, int y);
	string getName();
	void move(int new_x, int new_y);
	void attack(Player& opponent);
	void upgrade(unordered_map<string, unordered_map<string, int> > store);
private:
	int x, y, HP, ATK, MS, gold;
	string name;
};


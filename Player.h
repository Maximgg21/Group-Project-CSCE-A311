#pragma once
#include <map>
#include <string>
#include <map>

using namespace std;

class Player
{
public: 
	Player();
	Player(string n, int x, int y);
	string getName();
	int getGold();
	void setGold(int g);
	int getMS();
	void setMS(int m);
	int getATK();
	void setATK(int a);
	int getHP();
	void setHP(int h);
	void move(int new_x, int new_y);
	void attack(Player* opponent);
	int getX() { return x; }
	int getY() { return y; }
private:
	int x, y, HP, ATK, MS, gold;
	string name;
};


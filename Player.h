#pragma once
#include <string>

using namespace std;

class Player
{
public: 
	// Constructors
	Player();
	Player(string n, int x, int y);

	// Getters
	string getName();
	int getGold();
	int getMS();
	int getATK();
	int getHP();
	bool getCpu();
	void setGold(int g);
	int getX() { return x; }
	int getY() { return y; }

	// Setters
	void setMS(int m);
	void setATK(int a);
	void setHP(int h);
	void setCpu(bool b);

	// Functions
	void move(int new_x, int new_y);
	void attack(Player* opponent);
	void view_stats();
private:
	int x, y, HP, ATK, MS, gold;
	string name;
	bool cpu;
};


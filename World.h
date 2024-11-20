#pragma once
#include <vector>
#include <string>
using namespace std;

struct Cell {
	int resource;
	string display;
	Cell() {};
};

class World
{
public:
	World();
private:
	vector<vector<Cell>> world;
};


#include "World.h"
#include <iostream>

const int SIZE = 15;	// World size

World::World() : turn(0), world(SIZE, vector<Cell>(SIZE, Cell()))
{
	srand(time(NULL));

	cout << "P - player" << endl;
	cout << "G - gold" << endl;
	cout << "HP - health potion" << endl;
	cout << "SP - speed potion" << endl;
	cout << "PP - power potion" << endl;

	worldStore = new Store;

	regenerateWorld(7, 3, worldStore);	// First generation of the world
}

void World::placePlayers(int playerCount)
{
	/* Places players on the map */
	for (int i = 0; i < playerCount; i++) {
		pair<int, int> result = randomEmptyTile();
		int x = result.first;
		int y = result.second;

		Player* p = new Player(to_string(i + 1), x, y);
		if (i == 0) p->setCpu(false); // Makes it so only the first player is not a cpu.
		playerTurns.push(p);

		world[x][y].occupied = p;
		world[x][y].display = 'P' + world[x][y].occupied->getName();
	}
}

void World::print()
{
	// Print the map
	for (int i = 0; i < SIZE * 3 + 1; i++) {
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < SIZE; i++) {
		cout << '|';
		for (int j = 0; j < SIZE; j++) {
			cout << world[i][j].display << '|';
		}
		cout << endl;
	}

	for (int i = 0; i < SIZE * 3 + 1; i++) {
		cout << "-";
	}
	cout << endl;
}

void World::play()
{
	/*
		Print World at Start of Every Turn
	*/
	print();

	while (!playerTurns.empty())
	{
		// Grab first player
		Player* currPlayer = playerTurns.front();
		playerTurns.pop();

		// If player dead skip loop (this eliminates them from being added again)
		if (currPlayer->getHP() <= 0)
		{
			continue;
		}

		// Print world again
		print();

		// Announce turn
		cout << "It's " << currPlayer->getName() << "'s turn!" << endl;

		if (currPlayer->getCpu()) computer_turn(currPlayer);
		else {
			int choiceCount = currPlayer->getMS(); // Updated to grant player correct amount of turns
			int choice;
			for (int i = 0; i < choiceCount; i++)
			{
				do
				{
					// Prompt for player activity
					cout << "You have " << choiceCount - i << " actions left." << endl;
					cout << "(1) Attack" << endl;
					cout << "(2) Move" << endl;
					cout << "(3) Shop" << endl;
					cout << "----------" << endl;
					cin >> choice;

					// Ensure valid input
					if (choice < 1 || choice > 3) cout << "Invalid option--try again" << endl;
				} while (choice < 1 || choice > 3);

				if (choice == 1)
				{
					if (!attack_range(currPlayer))
					{
						i--;
					}
				}
				else if (choice == 2)
				{
					move_range(currPlayer);
				}
				else if (choice == 3)
				{
					// Store Access
					worldStore->accessStore(currPlayer);
				}

				// Add player to back
				playerTurns.push(currPlayer);

				// Clear screen after every turn
				//system("cls");

			}
		}
	}
}

void World::regenerateWorld(int goldAmount, int potionsAmount, Store* s)
{
	/* Generates new items on the map */
	for (int i = 0; i < potionsAmount; i++) {		// Generate potions from the store
		pair<int, int> result = randomEmptyTile();
		vector<string> spawnPotions = { "Small Power Potion", "Small Health Potion", "Small Speed Potion" };
		int x = result.first;
		int y = result.second;

		int randIndex = rand() % spawnPotions.size();		// Select a random item from the store
		world[x][y].cellItem = s->findItem(spawnPotions[randIndex]);
		switch (randIndex) {
		case 0:
			world[x][y].display = "PP";
			break;
		case 1:
			world[x][y].display = "HP";
			break;
		case 2:
			world[x][y].display = "SP";
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < goldAmount; i++) {				// Generate gold
		pair<int, int> result = randomEmptyTile();
		int x = result.first;
		int y = result.second;

		int randomGold = rand() % 9 + 1;

		world[x][y].gold = randomGold;
		world[x][y].display = 'G' + to_string(randomGold);
	}
}

pair<int, int> World::randomEmptyTile()
{
	/* Gets a random empty tile on the map */
	while (true) {
		int x = rand() % SIZE, y = rand() % SIZE;

		if (world[x][y].display == "  ")
		{
			return { x, y };
		}
	}
}

void World::computer_turn(Player* p)
{
	int cMoves = p->getMS();
	for (int i = 0; i < cMoves; i++) {
		bool scared = (p->getHP() <= 10); // If cpu has less than half health they will try to restore it
		// Save player position
		int pX = p->getX();
		int pY = p->getY();

		if (scared) {
			vector<pair<int, int>> items;

			// Iterate 1 block around player
			for (int xPos = pX - 1; xPos <= pX + 1; xPos++)
			{
				for (int yPos = pY - 1; yPos <= pY + 1; yPos++)
				{
					// ignore ourselves
					if (xPos == pX && yPos == pY) {} // do nothing
					else if (xPos < SIZE && xPos >= 0 && yPos < SIZE && yPos >= 0 && world[xPos][yPos].cellItem != nullptr)
					{
						// Store enemy player
						items.push_back({ xPos, yPos });
					}
				}
			}

			if (!items.empty()) { // If theres a nearby item the cpu will run to it.
				int newX = items[0].first;
				int newY = items[0].second;

				if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && world[newX][newY].occupied == nullptr)
				{
					// Handle logical aspect
					world[pX][pY].occupied = nullptr;
					world[newX][newY].occupied = p;
					p->move(newX, newY);

					// Handle visual aspec
					world[pX][pY].display = "  ";
					world[newX][newY].display = "P" + p->getName();

					if (world[newX][newY].gold != 0)
					{
						// Add gold to player
						p->setGold(p->getGold() + world[newX][newY].gold);
						// Remove gold from cell
						world[newX][newY].gold = 0;
					}

					if (world[newX][newY].cellItem != nullptr)
					{
						item_collection(p);
					}
				}
				else {
					std::string item;
					if (p->getGold() >= 10) item = "Large Health Potion";
					else if (p->getGold() >= 7) item = "Medium Health Potion";
					else item = "Small Health Potion";
					worldStore->accessStore(p, item);
				}
			}
		}
		else {
			vector<Player*> players;
			// Iterate 1 block around player
			for (int xPos = pX - 1; xPos <= pX + 1; xPos++)
			{
				for (int yPos = pY - 1; yPos <= pY + 1; yPos++)
				{
					// ignore ourselves
					if (xPos == pX && yPos == pY) {} // do nothing
					else if (xPos < SIZE && xPos >= 0 && yPos < SIZE && yPos >= 0 && world[xPos][yPos].occupied != nullptr)
					{
						// Store enemy player
						players.push_back(world[xPos][yPos].occupied);
					}
				}
			}
			if (!players.empty()) p->attack(players[0]);
			else {
				vector<pair<int, int>> validMoves;
				if (pX + 1 < 15) validMoves.push_back({ pX + 1, pY });
				if (pX - 1 < 15) validMoves.push_back({ pX - 1, pY });
				if (pY + 1 < 15) validMoves.push_back({ pX, pY + 1 });
				if (pY - 1 < 15) validMoves.push_back({ pX, pY - 1 });

				int t = rand() % validMoves.size();
				int newX = validMoves[t].first;
				int newY = validMoves[t].second;

				if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && world[newX][newY].occupied == nullptr)
				{
					// Handle logical aspect
					world[pX][pY].occupied = nullptr;
					world[newX][newY].occupied = p;
					p->move(newX, newY);

					// Handle visual aspec
					world[pX][pY].display = "  ";
					world[newX][newY].display = "P" + p->getName();

					if (world[newX][newY].gold != 0)
					{
						// Add gold to player
						p->setGold(p->getGold() + world[newX][newY].gold);
						// Remove gold from cell
						world[newX][newY].gold = 0;
					}

					if (world[newX][newY].cellItem != nullptr)
					{
						item_collection(p);
					}
				}
			}
		}
	}

}

bool World::attack_range(Player* p)
{
	vector<Player*> players;

	// Save player position
	int pX = p->getX();
	int pY = p->getY();

	// Iterate 1 block around player
	for (int xPos = pX - 1; xPos <= pX + 1; xPos++)
	{
		for (int yPos = pY - 1; yPos <= pY + 1; yPos++)
		{
			// ignore ourselves
			if (xPos == pX && yPos == pY) {} // do nothing
			else if (xPos < SIZE && xPos >= 0 && yPos < SIZE && yPos >= 0 && world[xPos][yPos].occupied != nullptr)
			{
				// Store enemy player
				players.push_back(world[xPos][yPos].occupied);
			}
		}
	}

	// Return early
	if (players.empty())
	{
		cout << "You can't attack anyone" << endl;
		return false;
	}


	// Print enemy players
	cout << "You can attack:";
	for (auto e : players)
	{
		cout << " " << e->getName();
	}
	cout << endl;

	// Decide who to attack
	string to_attack;

	do
	{
		cin >> to_attack;

		auto i = find_if(players.begin(), players.end(), [&](Player* e)
			{
				return e->getName() == to_attack;
			});

		if (i == players.end())
		{
			cout << "Can't attack that player. Reselect." << endl;
		}
		else
		{
			break;
		}
	} while (true);

	// Find the player to attack
	for (auto e : players)
	{
		// If match
		if (e->getName() == to_attack)
		{
			// Attack player
			p->attack(e);

			// If player dies from attack, remove from play
			if (e->getHP() <= 0)
			{
				int xE = e->getX();
				int yE = e->getY();

				// Logical 
				world[xE][yE].occupied = nullptr;
				// Visual
				world[xE][yE].display = "  ";
			}
		}
	}

	return true;
}

void World::move_range(Player* p)
{
	int choice;

	int xCombs[] = { 1,0,-1,0 };
	int yCombs[] = { 0,-1,0,1 };


	cout << "1-Right, 2-Up, 3-Left, 4-Down" << endl;
	do
	{
		cin >> choice;

		// Ensure values are correct
		if (choice < 1 || choice > 4)
		{
			cout << "No such move--try again" << endl;
		}
		else
		{
			int xP = p->getX();
			int yP = p->getY();

			int newX = xP + xCombs[choice - 1];
			int newY = yP + yCombs[choice - 1];

			if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && world[newX][newY].occupied == nullptr)
			{
				// Handle logical aspect
				world[xP][yP].occupied = nullptr;
				world[newX][newY].occupied = p;
				p->move(newX, newY);

				// Handle visual aspec
				world[xP][yP].display = "  ";
				world[newX][newY].display = ("P" + p->getName());

				if (world[newX][newY].gold != 0)
				{
					// Add gold to player
					p->setGold(p->getGold() + world[newX][newY].gold);
					// Remove gold from cell
					world[newX][newY].gold = 0;
				}

				if (world[newX][newY].cellItem != nullptr)
				{
					item_collection(p);
				}

				// close out of loop
				break;
			}
			else
			{
				cout << "Can't move there, choose again" << endl;
			}
		}


	} while (true);
}

void World::item_collection(Player* p)
{
	int xP = p->getX();
	int yP = p->getY();

	int tp = world[xP][yP].cellItem->type;
	int bf = world[xP][yP].cellItem->buff;

	// Decide on which stat to buff
	if (tp == 1)
	{
		p->setATK(p->getATK() + bf);
	}
	else if (tp == 2)
	{
		p->setHP(p->getHP() + bf);
	}
	else if (tp == 3)
	{
		p->setMS(p->getMS() + bf);
	}

	// Remove item from cell
	world[xP][yP].cellItem = nullptr;
}

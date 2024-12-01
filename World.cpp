#include "World.h"
#include <iostream>

const int SIZE = 15;	// World size

World::World() : world(SIZE, vector<Cell>(SIZE, Cell()))
{
	worldStore = new Store;

	placePlayers();

	cout << "Would you like to play with bots? (1) Yes / (0) No" << endl;
	cin >> playWithBots;

	regenerateWorld(7, 3, worldStore);	// First generation of the world

	// Print Legend
	cout << "\x1b[31m" << "P - player" << "\x1b[0m" << endl;
	cout << "\x1b[33m" << "G - gold" << "\x1b[0m" << endl;
	cout << "HP - health potion" << endl;
	cout << "SP - speed potion" << endl;
	cout << "PP - power potion" << endl;
}

World::~World()
{
	delete worldStore;
}

void World::placePlayers()
{
	/* Places players on the map */
	int playerCount;
	cout << "How many players would you like? (Max 9)" << endl;
	for (int i = 0; i < 1; i++) {
		cin >> playerCount;
		if (playerCount > 9 || playerCount < 2) {
			cout << "Invalid number of players. Try again! (Max 9)" << endl;
			i--;
		}
	}

	for (int i = 0; i < playerCount; i++) {
		pair<int, int> result = randomEmptyTile();
		int x = result.first;
		int y = result.second;

		Player* p = new Player(to_string(i + 1), x, y);
		
		if (i == 0 || !playWithBots) p->setCpu(false); // Makes it so only the first player is not a cpu.

		playerTurns.push(p);

		world[x][y].occupied = p;
		world[x][y].display = "\x1b[31mP" + world[x][y].occupied->getName() + "\x1b[0m";
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
	while (playerTurns.size() > 1)
	{
		// Grab first player
		Player* currPlayer = playerTurns.front();
		playerTurns.pop();
		bool hasAttacked = false;

		// If player dead skip loop (this eliminates them from being added again)
		if (currPlayer->getHP() <= 0)
		{
			int px = currPlayer->getX();
			int py = currPlayer->getY();
			world[py][px].occupied = nullptr;
			delete currPlayer;
			continue;
		}

		if (currPlayer->getCpu()) computer_turn(currPlayer);
		else {
			int choiceCount = currPlayer->getMS(); // Updated to grant player correct amount of turns
			int choice;
			for (int i = 0; i < choiceCount; i++)
			{
				do
				{
					// Print world again
					print();

					// Announce turn
					cout << "It's " << currPlayer->getName() << "'s turn!" << endl;

					// Prompt for player activity
					cout << "You have " << choiceCount - i << " actions left." << endl;
					cout << "\x1b[31m" << "(1) Attack" << "\x1b[0m" << endl;
					cout << "\x1b[32m" << "(2) Move" << "\x1b[0m" << endl;
					cout << "\x1b[33m" << "(3) Shop" << "\x1b[0m" << endl;
					cout << "\x1b[94m" << "(4) View Stats" << "\x1b[0m" << endl;
					cout << "\x1b[1;37m" << "(5) Skip" << "\x1b[0m" << endl;
					cout << "----------" << endl;

					while (!(cin >> choice)) {	// Checking for non-integer inputs
						cin.clear(); // Clear error state
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
						cout << "Invalid input. Try again: " << endl;
					}

					// Ensure valid input
					if (choice < 1 || choice > 5) cout << "Invalid option--try again" << endl;
				} while (choice < 1 || choice > 5);

				if (choice == 1)
				{
					if (hasAttacked) {
						cout << "You can only attack once per turn" << endl;
						i--;
					}
					else if (!attack_range(currPlayer))
					{
						i--;
					}
					else {
						hasAttacked = true;
					}
				}
				else if (choice == 2)
				{
					if (!move_range(currPlayer)) i--;
				}
				else if (choice == 3)
				{
					// Store Access
					if (!worldStore->accessStore(currPlayer)) i--;
				}
				else if (choice == 4)
				{
					currPlayer->view_stats();
					i--;
				}
				else if (choice == 5)
				{
					std::cout << "Turn Skipped." << std::endl;
				}	
			}
		}
		// Add player to back
		playerTurns.push(currPlayer);
    
		// Clear screen after every turn
		cout << string(10, '\n');

	}

	Player* winner = playerTurns.front();
	cout << "Player " << winner->getName() << " has won!!!" << endl;
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
		world[x][y].display = "\x1b[33mG" + to_string(randomGold) + "\x1b[0m";
	}
}

pair<int, int> World::randomEmptyTile()
{
	/* Gets a random empty tile on the map */
	int maxNumberOfRetries = world.size();
	for (int i = 0; i < maxNumberOfRetries; i++) {
		int x = rand() % SIZE, y = rand() % SIZE;
		if (world[x][y].display == "  ") return { x, y };
	}

	for (int i = 0; i < SIZE; i++) {	// If random tile wasn't found, find any empty tile
		for (int j = 0; j < SIZE; j++) {
			if (world[i][j].display == " ") return { i, j };
		}
	}

	throw runtime_error("No empty tiles found");	// If the map is full (no solution for this now)
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
				if (pX + 1 < SIZE) validMoves.push_back({ pX + 1, pY });
				if (pX - 1 < SIZE) validMoves.push_back({ pX - 1, pY });
				if (pY + 1 < SIZE) validMoves.push_back({ pX, pY + 1 });
				if (pY - 1 < SIZE) validMoves.push_back({ pX, pY - 1 });

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
	cout << "type the number who to attack" << endl;

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
				cout << "You killed Player " << e->getName() << endl;

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

bool World::move_range(Player* p)
{
	int choice;

	int yCombs[] = { 1,0,-1,0 };
	int xCombs[] = { 0,-1,0,1 };


	cout << "1-Right, 2-Up, 3-Left, 4-Down, 5-Exit" << endl;
	do
	{
		cin >> choice;

		if (choice == 5) return false;	// Exit

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
				return true;
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

	if (world[xP][yP].cellItem == nullptr) return;

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

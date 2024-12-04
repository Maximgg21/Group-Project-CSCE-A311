#include <string>
#include "Store.h"

Store::Store()
{
	std::vector<Item> itemList = { // Any new items should be added to this vector.
		{"Small Power Potion", "A potion that increases your ATK by 1.", 1, 5, 1, nullptr, nullptr},
		{"Medium Power Potion", "A potion that increases your ATK by 2.", 1, 7, 2, nullptr, nullptr},
		{"Large Power Potion", "A potion that increases your ATK by 3.", 1, 10, 3, nullptr, nullptr},
		{"Small Speed Potion", "A potion that increases your MS by 1.", 3, 10, 1, nullptr, nullptr},
		{"Medium Speed Potion", "A potion that increases your MS by 2.", 3, 15, 2, nullptr, nullptr},
		{"Large Speed Potion", "A potion that increases your MS by 3.", 3, 20, 3, nullptr, nullptr},
		{"Small Health Potion", "A potion that increases your HP by 3.", 2, 3, 3, nullptr, nullptr},
		{"Medium Health Potion", "A potion that increases your HP by 6.", 2, 5, 6, nullptr, nullptr},
		{"Large Health Potion", "A potion that increases your HP by 10.", 2, 8, 10, nullptr, nullptr}
	};

	shared_ptr<Item> current = nullptr;
	for (int i = 0; i < itemList.size(); i++) { // Constructs the linked list.
		if (i == 0) {
			head = make_shared<Item>(itemList[i]);
			current = head;
		}
		else if (!((i + 1) < itemList.size())) {
			tail = make_shared<Item>(itemList[i]);
			current->next = tail;
			tail->prev = current;
		}
		else {
			current->next = make_shared<Item>(itemList[i]);;
			shared_ptr<Item> temp = current->next;
			temp->prev = current;
			current = temp;
		}
	}
}

bool Store::accessStore(Player* user, string item) // Opens the store and lists the items that a player can buy to upgrade their stats
{
	std::cout << "You have " << user->getGold() << " Gold" << std::endl;
	std::cout << "What would you like to buy?" << std::endl << "(Type the item name or 'exit' to leave)" << std::endl << std::endl;

	shared_ptr<Item> temp = head;
	if (temp == nullptr) {
		std::cout << "You've purchased the entire store!" << std::endl << std::endl; // This was used for demo purposes, I assume some items will never be "out of stock" so this will never be used.
		return true;
	}

	while (temp != nullptr) {		// List the items in the store
		std::cout << temp->name << " - " <<
			temp->description << " - " << temp->price << " gold" << std::endl << std::endl;
		temp = temp->next;
	}

	std::string order;
	cin.ignore();
	if (item == "") getline(cin, order);		// Get the user's desired item.
	if (order == "exit") {
		cout << "You left the store." << endl;
		return false;
	}

	temp = findItem(order);

	if (temp == nullptr) {
		std::cout << "There is no such item in the store." << std::endl;
		return false;
	}
	else if (user->getGold() < temp->price) {
		std::cout << "You don't have enough gold to buy this item." << std::endl;
		return false;
	}
	else {

	}

	purchaseItem(temp, user);

	std::cout << "You bought the item. Your stats now are: " << "HP = " << user->getHP() << ", ATK = " << user->getATK() << ", MS = " << user->getMS() << std::endl;

	return true;
}

shared_ptr<Item> Store::findItem(std::string n) // Returns pointer to desired item for easy access.
{
	shared_ptr<Item> tHead = head, tTail = tail, i = nullptr;
	while (tHead != tTail && tHead->prev != tTail) { // Two pointers traverse list from each end to cut time in half.
		if (tHead->name == n) {
			i = tHead;
			break;
		}
		else if (tTail->name == n) {
			i = tTail;
			break;
		}
		else {
			tHead = tHead->next;
			tTail = tTail->prev;
		}
	}
	if (tHead == tTail && tHead->name == n) i = tHead;

	return i;
}

void Store::purchaseItem(shared_ptr<Item> i, Player* u) // Applies buff, removes gold, and if neccesary, deletes item from store.
{
	bool toDelete = false; // If the purchased item can only be purchased once, this becomes true.
	switch (i->type) {
	case 1:
		u->setATK(u->getATK() + i->buff);
		u->setGold(u->getGold() - i->price);
		toDelete = true; // I made items that improve ATK and MS one time purchases so a character can't be insanely stacked, feel free to change this :)
		break;
	case 2:
		u->setHP(u->getHP() + i->buff);
		u->setGold(u->getGold() - i->price);
		break;
	case 3:
		u->setMS(u->getMS() + i->buff);
		u->setGold(u->getGold() - i->price);
		toDelete = true;
		break;
	default:
		break;
	}

	if (toDelete) {
		if (i == head) {
			head = head->next;
			head->prev = nullptr;
		}
		else if (i == tail) {
			tail = tail->prev;
			tail->next = nullptr;
		}
		else {
			shared_ptr<Item> n = i->next, p = i->prev;
			p->next = n;
			n->prev = p;
		}
	}

}

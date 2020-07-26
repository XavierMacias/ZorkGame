#include <iostream>
#include "player.h"

using namespace std;

// ----------------------------------------------------
Player::Player(const char* name, const char* description, Room* room) : 
	Creature(name,description, room)
{
	type = PLAYER;

}

// ----------------------------------------------------
Player::~Player()
{
}

// ----------------------------------------------------
void Player::Look() const {
	
	cout << "\n" << name << "\n";
	cout << description << "\n";
}
// ----------------------------------------------------
void Player::Inventory() const {
	cout << "ITEMS: \n";
	if (items.empty()) {
		cout << "You don't have any items.\n";
	}
	else {
		for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
		{
			cout << (*it)->name << "\n";
		}
	}

	cout << "EQUIPMENT: \n";
	if (weapon == NULL) {
		cout << "You don't have any equiped weapon.\n";
	}
	else {
		cout << "Weapon: " << weapon << "\n";
	}
	
	if (armour == NULL) {
		cout << "You don't have any equiped armour.\n";
	}
	else {
		cout << "Armour: " << armour << "\n";
	}

	cout << "STATS: \n";
	cout << "Attack: " << attack << "\n";
	cout << "Defense: " << defense << "\n";

}
// ----------------------------------------------------
Item* Player::HaveItem(string item) {
	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		if ((*it)->name == item) {
			return (Item*)*it;
		}
	}
	return NULL;
}
// ----------------------------------------------------
void Player::Equip(string name) {
	if (HaveItem(name) != NULL) {
		Item* item = HaveItem(name);
		if (item->type == ARMOUR) {
			armour = item;
			defense += 5;
			cout << "You equiped a shield.\n";
		}
		else if(item->type == WEAPON) {
			weapon = item;
			attack += 5;
			cout << "You equiped a sword.\n";
		}
		else {
			cout << "You can't equip this item.\n";
		}
	}
	else {
		cout << "You don't have this item to equip.\n";
	}
	
}

void Player::Unequip(string item) {
	if (weapon->name == item) {
		weapon = NULL;
		attack -= 5;
		cout << "You unequiped the sword.\n";
	}
	else if (armour->name == item) {
		armour = NULL;
		defense -= 5;
		cout << "You unequiped the shield.\n";
	}
	else {
		cout << "You can't unequip this";
	}

}

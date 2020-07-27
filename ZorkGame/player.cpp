#include <iostream>
#include "player.h"

using namespace std;

// ----------------------------------------------------
Player::Player(const char* name, const char* description, Room* room) : 
	Creature(name,description, room)
{
	type = PLAYER;
	actualRoom = room;

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
		cout << "Weapon: " << weapon->name << "\n";
	}
	
	if (armour == NULL) {
		cout << "You don't have any equiped armour.\n";
	}
	else {
		cout << "Armour: " << armour->name << "\n";
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
Room* Player::Go(string direction) {
	Exit* ex = actualRoom->GetExit(direction);
	if (ex == NULL) {
		cout << "You can't go in this direction.\n";
	}
	else {
		if (ex->origin->name == actualRoom->name) {
			actualRoom = ex->destination;
		}
		else if(ex->destination->name == actualRoom->name) {
			actualRoom = ex->origin;
		}
		cout << "You go in direction " << direction << ".\n";
		return actualRoom;
	}
	return NULL;
}
// ----------------------------------------------------
void Player::Take(string name) {
	list<Entity*> roomElements = actualRoom->elements;
	bool find = false;
	for (list<Entity*>::const_iterator it = roomElements.begin(); it != roomElements.cend(); ++it)
	{
		if ((*it)->name == name) {
			find = true;
			items.push_back((*it));
			cout << "You take the " << name << ".\n";
			actualRoom->elements.remove(*it);
			break;
		}
	}
	if (!find) {
		cout << "This object isn't in this room.\n";
	}
}
// ----------------------------------------------------
void Player::Drop(string name) {
	if (HaveItem(name) != NULL) {
		Item* item = HaveItem(name);
		items.remove(item);
		actualRoom->elements.push_back(item);
		cout << "You drop the " << name << " in this room.\n";
	}
	else {
		cout << "You don't have this item in the inventory (Remember to unequip the weapons before drop them!).\n";
	}
}
// ----------------------------------------------------
void Player::Equip(string name) {
	if (HaveItem(name) != NULL) {
		Item* item = HaveItem(name);
		if (item->item_type == ARMOUR) {
			items.remove(item);
			armour = item;
			defense += item->defense_power;
			cout << "You equiped a shield.\n";
		}
		else if(item->item_type == WEAPON) {
			items.remove(item);
			weapon = item;
			attack += item->attack_power;
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

void Player::Unequip(string name) {
	if (weapon->name == name) {
		Item* item = weapon;
		weapon = NULL;
		attack -= item->attack_power;
		items.push_back(item);
		cout << "You unequiped the sword.\n";
	}
	else if (armour->name == name) {
		Item* item = armour;
		armour = NULL;
		defense -= item->defense_power;
		items.push_back(item);
		cout << "You unequiped the shield.\n";
	}
	else {
		cout << "You can't unequip this";
	}

}

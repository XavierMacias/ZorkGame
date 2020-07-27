#include <iostream>
#include "player.h"

using namespace std;

// ----------------------------------------------------
Player::Player(const char* name, const char* description, Room* room, int max) : 
	Creature(name,description, room, max)
{
	type = PLAYER;
	actualRoom = room;

}

// ----------------------------------------------------
Player::~Player()
{
}

// ----------------------------------------------------
void Player::Look(string name) const 
{
	list<Entity*> roomElements = actualRoom->elements;
	bool find = false;
	for (list<Entity*>::const_iterator it = roomElements.begin(); it != roomElements.cend(); ++it)
	{
		if ((*it)->name == name) {
			if ((*it)->type == CREATURE || (*it)->type == ITEM || (*it)->type == NPC) {
				find = true;
				(*it)->Look();
			}
		}
	}
	if (!find) {
		cout << "You can't look that.\n";
	}

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
	cout << "Health Points: " << hp << "/" << maxHP << "\n";
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
		if (ex->locked) {
			cout << "This path is blocked by a big iron door.\n";
			return NULL;
		}
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
			cout << "You equiped a " << item->name << ".\n";
		}
		else if(item->item_type == WEAPON) {
			items.remove(item);
			weapon = item;
			attack += item->attack_power;
			cout << "You equiped a " << item->name << ".\n";
		}
		else {
			cout << "You can't equip this item.\n";
		}
	}
	else {
		cout << "You don't have this item to equip.\n";
	}
	
}
// ----------------------------------------------------
void Player::Unequip(string name) {
	if (weapon->name == name) {
		Item* item = weapon;
		weapon = NULL;
		attack -= item->attack_power;
		items.push_back(item);
		cout << "You unequiped the " << item->name << ".\n";
	}
	else if (armour->name == name) {
		Item* item = armour;
		armour = NULL;
		defense -= item->defense_power;
		items.push_back(item);
		cout << "You unequiped the " << item->name << ".\n";
	}
	else {
		cout << "You can't unequip this.\n";
	}

}
// ----------------------------------------------------
bool Player::Use(string name) {
	if (HaveItem(name) == NULL) {
		cout << "You don't have this item to use.\n";
		return false;
	}
	Item* item = HaveItem(name);
	if (item->item_type == HEALTH && item->name == name) {
		if (hp == maxHP) {
			cout << "Your health is maximal!\n";
			return false;
		}
		hp += item->heal_power;
		if (hp > maxHP) {
			hp = maxHP;
		}
		cout << "You use the " << item->name <<  " and restored HP!\n";
		items.remove(item);
		return true;
	}
	Exit* lockedExit = actualRoom->GetLockedExit();
	if (lockedExit == NULL) {
		cout << "You can't use this item here.\n";
		return false;
	}
	if (item != lockedExit->key) {
		cout << "This item doesn't work here.\n";
		return false;
	}

	actualRoom->GetLockedExit()->locked = false;
	items.remove(item);
	cout << "You unlocked the door in the path with the " << item->name << ".\n";
	return true;
}
// ----------------------------------------------------
bool Player::Talk(string name) {
	if (actualRoom->GetCreature(name) == NULL) {
		cout << "You can't talk with it now.\n";
		return false;
	}
	actualRoom->GetCreature(name)->Talk();
	return true;
}
// ----------------------------------------------------
bool Player::Attack(string name) {
	if (actualRoom->GetCreature(name) == NULL) {
		cout << "You can't attack this.\n";
		return false;
	}
	Creature* cr = actualRoom->GetCreature(name);
	if (cr->type == NPC) {
		cout << "You can't attack this person.\n";
		return false;
	}
	while (!cr->IsDead() || !IsDead()) {
		TurnAttack(this, cr);
		if (cr->IsDead()) {
			break;
		}
		TurnAttack(cr, this);
		if (IsDead()) {
			break;
		}
	}
	if (cr->IsDead()) {
		cout << "You defeat " << cr->name << "!\n";
	}
	else {
		cout << "You dead! GAME OVER!\n";
		exit(0);
	}
	return true;
}
// ----------------------------------------------------
void Player::TurnAttack(Creature* attacker, Creature* defender) {
	int hurt = (attacker->attack * 2) / defender->defense;
	hurt += rand() % 3;
	defender->hp -= hurt;
	if (attacker == this) {
		cout << "You attack " << defender->name << " and it losts " << hurt << "HP!\n";
	}
	else {
		cout << attacker->name << " attack you and you lost " << hurt << "HP!\n";
	}
	
}


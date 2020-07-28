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
bool Player::Look(string name) const 
{
	list<Entity*> roomElements = actualRoom->elements; 
	for (list<Entity*>::const_iterator it = roomElements.begin(); it != roomElements.cend(); ++it)
	{
		if ((*it)->name == name) { // you only can look creatures, items and NPCs.
			if ((*it)->type == CREATURE || (*it)->type == ITEM || (*it)->type == NPC) {
				if ((*it)->type == ITEM) {
					Item* item = (Item*)*it;
					if (!item->ContainerIsOpened()) {
						cout << "You can't look that.\n";
						return false;
					}

				}
				(*it)->Look();
				return true;
			}
		}
	}
	cout << "You can't look that.\n";
	return false;

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
			cout << (*it)->name << "\n"; // show the items the player has
		}
	}

	cout << "EQUIPMENT: \n"; // player's equipment
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

	cout << "STATS: \n"; // player's stats
	cout << "Health Points: " << hp << "/" << maxHP << "\n";
	cout << "Attack: " << attack << "\n";
	cout << "Defense: " << defense << "\n";

}
// ----------------------------------------------------
Item* Player::HaveItem(string item) { // check if the player has an item in its inventory
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
		cout << "You can't go in this direction.\n"; // you can go in this direction?
	}
	else {
		if (ex->locked) {
			cout << "This path is blocked by a big iron door.\n"; // the exit is locked?
			return NULL;
		}
		if (ex->origin->name == actualRoom->name) {	
			actualRoom = ex->destination;
		}
		else if(ex->destination->name == actualRoom->name) {
			actualRoom = ex->origin;
		}
		cout << "You go in direction " << direction << ".\n"; // go to this direction and change actual room
		return actualRoom;
	}
	return NULL;
}
// ----------------------------------------------------
bool Player::Take(string name) {
	list<Entity*> roomElements = actualRoom->elements; // take the item if it's in the actual room
	for (list<Entity*>::const_iterator it = roomElements.begin(); it != roomElements.cend(); ++it)
	{
		if ((*it)->type == ITEM) {
			Item* item = (Item*)*it;
			if (item->name == name && item->ContainerIsOpened()) {
				if (!item->canTake) {
					cout << "You can't take this item with you.\n";
					return false;
				}
				items.push_back(item);
				cout << "You take the " << name << ".\n";
				actualRoom->elements.remove(*it);
				if (item->container != NULL) {
					item->container->child = NULL;
				}
				return true;
			}
		}
		
	}
	cout << "You can't take this.\n";
	return false;
}
// ----------------------------------------------------
void Player::Drop(string name) {
	if (HaveItem(name) != NULL) { // drop the item in the room if the player has it
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
bool Player::Equip(string name) {
	if (HaveItem(name) != NULL) { // equip the item if the player hasn't equip something already
		Item* item = HaveItem(name);
		if (item->item_type == ARMOUR) {
			if (armour != NULL) {
				cout << "You already have an armour equiped.\n";
				return false;
			}
			items.remove(item);
			armour = item;
			defense += item->defense_power;
			cout << "You equiped a " << item->name << ".\n";
			return true;
		}
		else if(item->item_type == WEAPON) {
			if (weapon != NULL) {
				cout << "You already have a weapon equiped.\n";
				return false;
			}
			items.remove(item);
			weapon = item;
			attack += item->attack_power;
			cout << "You equiped a " << item->name << ".\n";
			return true;
		}
		cout << "You can't equip this item.\n";
		return false;
	}
		
	cout << "You don't have this item to equip.\n";
	return false;
	
}
// ----------------------------------------------------
bool Player::Unequip(string name) {
	if (weapon != NULL) { // unequip the item if the player has something equiped
		if (weapon->name == name) {
			Item* item = weapon;
			weapon = NULL;
			attack -= item->attack_power;
			items.push_back(item);
			cout << "You unequiped the " << item->name << ".\n";
			return true;
		}
	}
	if (armour != NULL) {
		if (armour->name == name) {
			Item* item = armour;
			armour = NULL;
			defense -= item->defense_power;
			items.push_back(item);
			cout << "You unequiped the " << item->name << ".\n";
			return true;
		}
	}

	cout << "You can't unequip this.\n";
	return false;

}
// ----------------------------------------------------
bool Player::Use(string name) {
	if (HaveItem(name) == NULL) {
		cout << "You don't have this item to use.\n";
		return false;
	}
	Item* item = HaveItem(name);
	if (item->item_type == HEALTH && item->name == name) { // use health item, like a potion
		if (hp == maxHP) {
			cout << "Your health is maximal!\n";
			return false;
		}
		hp += item->heal_power; // recover HP
		if (hp > maxHP) {
			hp = maxHP;
		}
		cout << "You use the " << item->name <<  " and restored HP!\n";
		items.remove(item);
		return true;
	}
	if (item->item_type == STAR && item->name == name) { // use sacred star
		cout << "You use the power of the sacred star!\nYOU WIN THE GAME! CONGRATULATIONS!\n"; // you win the game
		exit(0); // exit game
	}
	cout << "You can't use this here.\n";
	return false;
	
}
// ----------------------------------------------------
bool Player::Open(string name) {
	list<Entity*> roomElements = actualRoom->elements;
	for (list<Entity*>::const_iterator it = roomElements.begin(); it != roomElements.cend(); ++it)
	{
		if ((*it)->type == ITEM) { // open item is it can be opened
			Item* item = (Item*)*it;
			if (item->name == name && !item->opened && !item->canTake) {
				if (item->locked) {
					cout << "This " << item->name << " is locked.\n";
					return false;
				}
				cout << "You open the " << name << ".\n";
				cout << "There is a " << item->child->name << " inside.\n"; // item inside
				item->opened = true;
				return true;
			}
		}
		
	}
	cout << "You can't open this object.\n";
	return false;
}
// ----------------------------------------------------
bool Player::Unlock(string name, string direction) {
	if (HaveItem(name) == NULL) {
		cout << "You don't have this item to use.\n";
		return false;
	}
	Item* item = HaveItem(name);
	Exit* lockedExit = actualRoom->GetLockedExit(direction); // lockedExits?
	Item* lockedItem = actualRoom->GetLockedItem(direction); // lockedItems?
	if (lockedExit != NULL) { // unlock exit
		if (item != lockedExit->key) { // check if is the correct key
			cout << "This item doesn't work here.\n";
			return false;
		}
		actualRoom->GetLockedExit(direction)->locked = false;
		items.remove(item);
		cout << "You unlocked the door in the " << direction << " path with the " << item->name << ".\n";
		return true;
		
	}
	if (lockedItem != NULL) { // unlock item (like chest)
		if (item != lockedItem->key) { // check if is the correct key
			cout << "This item doesn't work here.\n";
			return false;
		}
		actualRoom->GetLockedItem(direction)->locked = false;
		items.remove(item);
		cout << "You unlocked the " << direction << " with the " << item->name << ".\n";
		return true;
	}

	cout << "You can't use this item here.\n";
	return false;

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
bool Player::Loot(string name) {

	Creature* cr = actualRoom->GetCreature(name);
	if (cr == NULL) {
		cout << "You can't loot this.\n";
		return false;
	}
	if (!cr->IsDead()) {
		cout << "You can't loot something if it's alive.\n";
		return false;
	}
	if (cr->weapon == NULL && cr->armour == NULL && cr->inventory == NULL) {
		cout << "It hasn't anything to loot.\n";
		return false;
	}

	if (cr->weapon != NULL) { // loot weapon
		items.push_back(cr->weapon);
		cout << "You obtain a " << cr->weapon->name << ".\n";
		cr->weapon = NULL;
	}
	if (cr->armour != NULL) { // loot armour
		items.push_back(cr->armour);
		cout << "You obtain a " << cr->armour->name << ".\n";
		cr->armour = NULL;
	}
	if (cr->inventory != NULL) { // loot object
		items.push_back(cr->inventory);
		cout << "You obtain a " << cr->inventory->name << ".\n";
		cr->inventory = NULL;
	}
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
	if (cr->IsDead()) {
		cout << cr->name << " is already dead!\n";
		return false;
	}
	TurnAttack(this, cr); // attack enemy
	if (cr->IsDead()) {
		cout << "You defeat " << cr->name << "!\n"; // kill enemy
		if (cr->weapon != NULL || cr->armour != NULL || cr->inventory != NULL) { // check if enemy has loot
			cout << cr->name << " dropped something when it died!\n";
		}
		return true;
	}
	TurnAttack(cr, this); // enemy attack you
	if (IsDead()) {
		cout << "You dead! GAME OVER!\n"; // enemy kills you
		exit(0);
	}

	return true;
}
// ----------------------------------------------------
void Player::TurnAttack(Creature* attacker, Creature* defender) {
	int hurt = (attacker->attack * 2) / defender->defense;
	hurt += rand() % 3;
	defender->hp -= hurt;
	if (defender->hp < 0) {
		defender->hp = 0;
	}
	if (attacker == this) {
		cout << "You attack " << defender->name << " and it losts " << hurt << "HP! ("<< defender->hp <<"/" << defender->maxHP << ") \n";
	}
	else {
		cout << attacker->name << " attack you and you lost " << hurt << "HP! (" << hp << "/" << maxHP << ") \n";
	}
	
}


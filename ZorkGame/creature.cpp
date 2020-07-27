#include "creature.h"

// ----------------------------------------------------
Creature::Creature(const char* name, const char* description, Room* room, int max) :
	Entity(name, description, (Entity*)room)
{
	type = CREATURE;
	attack = defense = 1;
	maxHP = hp = max;
	weapon = NULL;
	armour = NULL;
	room->elements.push_back(this);
	//if (one_way == false)
	//	destination->container.push_back(this);
}

// ----------------------------------------------------
Creature::~Creature()
{
}

// ----------------------------------------------------

bool Creature::IsDead() const {
	return hp <= 0;
}
// ----------------------------------------------------
void Creature::Look() const {

	if (IsDead()) {
		cout << "This is the dead body of " << name << ".\n";
	}
	else {
		cout << "\n" << name << "\n";
		cout << description << "\n";
	}
	
	
}

// ----------------------------------------------------
void Creature::Talk() const {
	if (!IsDead()) {
		cout << text;
	}
	else {
		cout << "You can't talk with it because it's dead!\n";
	}
	
}

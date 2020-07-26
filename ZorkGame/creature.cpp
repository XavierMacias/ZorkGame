#include "creature.h"

// ----------------------------------------------------
Creature::Creature(const char* name, const char* description, Room* room) :
	Entity(name, description, (Entity*)room)
{
	type = CREATURE;
	attack = defense = 1;
	weapon = NULL;
	armour = NULL;
	//if (one_way == false)
	//	destination->container.push_back(this);
}

// ----------------------------------------------------
Creature::~Creature()
{
}

// ----------------------------------------------------

void Creature::Look() const {

	cout << "\n" << name << "\n";
	cout << description << "\n";
}

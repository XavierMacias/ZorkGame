#include <iostream>
#include <string>
#include "exit.h"
#include "creature.h"
#include "room.h"

// ----------------------------------------------------
Room::Room(const char* name, const char* description) :
	Entity(name, description, (Entity*)this)
{
	type = ROOM;
}

// ----------------------------------------------------
Room::~Room()
{
}

// ----------------------------------------------------
void Room::Look() const
{
	cout << "\n" << name << "\n";
	cout << description;

	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		//if ((*it)->type == EXIT && (*it)->room->name == name)
		if ((*it)->type == EXIT) 
		{
			Exit* ex = (Exit*)*it;
			if (ex->destination->name == name) {
				ex->Look(1);
			}
			else if (ex->origin->name == name) {
				ex->Look(0);
			}
			
			//cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->name;
		}
	}

	// List items --
	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == ITEM)// && (*it)->room->name == name)
		{
			Item* item = (Item*)*it;
			if (item->ContainerIsOpened()) {
				cout << "\nThere is an item here: " << item->name;
			}
			
		}
	}

	// List creatures --
	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == CREATURE || (*it)->type == NPC) //&& (*it)->room->name == name)
		{
			Creature* cr = (Creature*)*it;
			if (cr->IsDead()) {
				cout << "\nThere is the dead body of " << cr->name;
			}
			else {
				cout << "\nThere is someone else here: " << cr->name;
			}
			
			//if (cr->IsAlive() == false)
			//	cout << " (dead)";
		}
	}

	cout << "\n";
}

// ----------------------------------------------------
Exit* Room::GetExit(string direction)
{
	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (ex->destination->name == name && ex->lead == direction) {
				return ex;
			}
			else if (ex->origin->name == name && ex->direction == direction) {
				return ex;
			}
		}
	}

	return NULL;
}
// ----------------------------------------------------
Exit* Room::GetLockedExit(string direction)
{
	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (ex->locked && ((ex->direction == direction && this == ex->origin) || (ex->lead == direction && this == ex->destination))) {
				return ex;
			}
		}
	}

	return NULL;
}
// ----------------------------------------------------
Creature* Room::GetCreature(string name) {

	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == CREATURE || (*it)->type == NPC)
		{
			return (Creature*)(*it);
		}
	}

	return NULL;
}
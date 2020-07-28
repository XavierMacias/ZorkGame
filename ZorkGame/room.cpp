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

	// List exits --
	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			if (ex->destination->name == name) { // depending of the point of view the direction changes
				ex->Look(1);
			}
			else if (ex->origin->name == name) {
				ex->Look(0);
			}
		}
	}

	// List items --
	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			Item* item = (Item*)*it; // items inside chests or other creatures doesn't show in the map initially
			if (item->ContainerIsOpened() && item->container == NULL && item->appear) { 
				cout << "\nThere is an item here: " << item->name;
			}
			
		}
	}

	// List creatures --
	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == CREATURE || (*it)->type == NPC) 
		{
			Creature* cr = (Creature*)*it;
			if (cr->IsDead()) {
				cout << "\nThere is the dead body of " << cr->name;
			}
			else {
				cout << "\nThere is someone else here: " << cr->name;
			}
		}
	}

	cout << "\n";
}

// ----------------------------------------------------
Exit* Room::GetExit(string direction) // obtain the exit of the room in this direction
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
Exit* Room::GetLockedExit(string direction) // obtain the LOCKED exit of this room in this direction
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
Item* Room::GetLockedItem(string name) // obtain the LOCKED item of this room with this name
{
	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			Item* item = (Item*)*it;
			if (item->locked && item->name == name) {
				return item;
			}
		}
	}

	return NULL;
}
// ----------------------------------------------------
Creature* Room::GetCreature(string name) { // obtain the creature or NPC of this room with this name

	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == CREATURE || (*it)->type == NPC)
		{
			return (Creature*)(*it);
		}
	}

	return NULL;
}
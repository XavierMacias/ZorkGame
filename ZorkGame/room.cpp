#include <iostream>
#include "exit.h"
#include "room.h"

// ----------------------------------------------------
Room::Room(const char* title, const char* description) :
	Entity(title, description, (Entity*)this)
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
		if ((*it)->type == ITEM && (*it)->room->name == name)
		{
			Item* item = (Item*)*it;
			cout << "\nThere is an item here: " << item->name;
		}
	}

	// List creatures --
	for (list<Entity*>::const_iterator it = elements.begin(); it != elements.cend(); ++it)
	{
		if ((*it)->type == CREATURE && (*it)->room->name == name)
		{
			Creature* cr = (Creature*)*it;
			cout << "\nThere is someone else here: " << cr->name;
			//if (cr->IsAlive() == false)
			//	cout << " (dead)";
		}
	}

	cout << "\n";
}

// ----------------------------------------------------
/*Exit* Room::GetExit(const string& direction) const
{
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			//if (Same(ex->GetNameFrom(this), direction))
			//	return ex;
		}
	}
	
	return NULL;
}*/
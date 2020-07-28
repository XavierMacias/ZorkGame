#pragma once
#ifndef __Room__
#define __Room__
#include <string>
#include <list>
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"

class Entity;
class Exit;
class Creature;

using namespace std;

class Room : public Entity
{
	public:
		Room(const char* name, const char* description);
		~Room();

		void Look() const;
		Exit* GetExit(string direction);
		Exit* GetLockedExit(string direction);
		Item* GetLockedItem(string item);
		Creature* GetCreature(string name);

	public:
		list<Entity*> elements; // all the elements of the room
};
#endif


#ifndef __Creature__
#define __Creature__
#pragma once

#include <string>
#include "entity.h"
#include "room.h"
#include "item.h"

using namespace std;

class Entity;
class Room;
class Item;

class Creature : public Entity
{
	public:
		Creature(const char* name, const char* description, Room* room);
		~Creature();

		virtual void Look() const;

		//bool IsAlive() const;
	public:
		int attack;
		int defense;
		Item* weapon;
		Item* armour;
};

#endif


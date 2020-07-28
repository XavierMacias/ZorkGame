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
		Creature(const char* name, const char* description, Room* room, int maxHP);
		~Creature();

		bool IsDead() const;
		virtual void Look() const;
		void Talk() const;
		void SetWeapon(Item* weapon);
		void SetArmour(Item* armour);

	public:
		int hp;
		int maxHP;
		int attack;
		int defense;
		Item* weapon;
		Item* armour;
		Item* inventory;
		string text;
};

#endif


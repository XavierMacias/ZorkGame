#ifndef __Player__
#define __Player__
#pragma once

#include "creature.h"

using namespace std;

class Entity;
class Creature;
class Item;
class Room;

class Player : public Creature
{
	public:
		Player(const char* name, const char* description, Room* room);
		~Player();

		void Look() const;
		void Inventory() const;
		Item* HaveItem(string item);
		void Equip(string item);
		void Unequip(string item);
	public:
		list<Entity*> items;
};

#endif //__Player__


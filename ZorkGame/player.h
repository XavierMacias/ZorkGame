#ifndef __Player__
#define __Player__
#pragma once

#include "creature.h"
#include "exit.h"

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
		Room* Go(string direction);
		void Take(string item);
		void Drop(string item);
		void Equip(string item);
		void Unequip(string item);
	public:
		list<Entity*> items;
		Room* actualRoom;
};

#endif //__Player__


#pragma once
#include "creature.h"

using namespace std;

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


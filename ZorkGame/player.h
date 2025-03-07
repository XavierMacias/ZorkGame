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
		Player(const char* name, const char* description, Room* room, int maxHP);
		~Player();

		bool Look(string entity) const;
		void Inventory() const;
		Item* HaveItem(string item);
		Room* Go(string direction);
		bool Take(string item);
		void Drop(string item);
		bool Equip(string item);
		bool Unequip(string item);
		bool Use(string item);
		bool Talk(string creature);
		bool Open(string item);
		bool Unlock(string item, string direction);
		bool Loot(string enemy);
		bool Attack(string enemy);
		void TurnAttack(Creature* attacker, Creature* defender);
	public:
		list<Entity*> items; // the items that actually have the player
		Room* actualRoom; // the room when actually is the player
};

#endif //__Player__


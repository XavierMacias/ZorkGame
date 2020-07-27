#pragma once
#ifndef __Item__
#define __Item__
#include <string>
#include "entity.h"
#include "room.h"

using namespace std;

class Room;

enum ItemType
{
	COMMON,
	HEALTH,
	WEAPON,
	ARMOUR
};

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Room* room, ItemType item_type, Item* container = NULL);
	~Item();

	void Look() const;
	bool ContainerIsOpened() const;

public:
	ItemType item_type;
	Item* container;
	Item* child;
	int attack_power;
	int defense_power;
	int heal_power;
	bool opened;
	bool canTake;
};
#endif


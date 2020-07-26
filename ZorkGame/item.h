#pragma once
#include <string>
#include "entity.h"
#include "room.h"

using namespace std;

enum ItemType
{
	COMMON,
	WEAPON,
	ARMOUR
};

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Room* room, ItemType item_type);
	~Item();

	void Look() const;

public:
	ItemType item_type;
};


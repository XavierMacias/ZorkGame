#include "item.h"

// ----------------------------------------------------
Item::Item(const char* name, const char* description, Room* room, ItemType itemType) :
	Entity(name, description, (Entity*)room)
{
	type = ITEM;
	item_type = itemType;

	//if (one_way == false)
	//	destination->container.push_back(this);
}

// ----------------------------------------------------
Item::~Item()
{
}

// ----------------------------------------------------

void Item::Look() const {

	cout << "\n" << name << "\n";
	cout << description << "\n";
}

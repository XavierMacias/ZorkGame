#include "item.h"

// ----------------------------------------------------
Item::Item(const char* name, const char* description, Room* room, ItemType itemType, Entity* container) :
	Entity(name, description, (Entity*)room), container(container)
{
	type = ITEM;
	item_type = itemType;
	attack_power = 0; // power attack for weapons
	defense_power = 0; // defense power for armours
	heal_power = 0; // heal power for potions
	opened = true; // this item is opened (for chests)
	canTake = true; // you can take this item to the inventory (for example, you cannot take a chest)
	key = NULL; // the key to open this item (for chests)
	child = NULL; // this item contains another item inside (for chests)
	appear = true; // this item appears in the room look
	locked = false; // this item is locked (for chests)
	room->elements.push_back(this);
	if (container != NULL) {
		container->child = this;
		if (container->type == CREATURE) {
			Creature* cr = (Creature*)container;
			cr->inventory = this; // the creature has this item in it inventory
		}
	}
}

// ----------------------------------------------------
Item::~Item()
{
}
// ----------------------------------------------------
bool Item::ContainerIsOpened() const {
	if (container != NULL) {
		if (container->type == ITEM) {
			Item* it = (Item*)container; // check if the container of the item is opened
			return it->opened;           // this is for items that are inside chests, for example
		}
		
	}

	return true;
}

// ----------------------------------------------------

void Item::Look() const {

	if (ContainerIsOpened() && container != NULL) {
		cout << "\n" << name << "\n";
		cout << "It's in the " << container->name << ".\n"; // if the item is inside another thing...
	}
	else if(opened && child != NULL) {
		cout << "\n" << name << "\n";
		cout << "There is a "<< child->name << " inside...\n"; // if the item HAS another thing inside it...
	}
	else {
		cout << "\n" << name << "\n";
		cout << description << "\n";
	}
}




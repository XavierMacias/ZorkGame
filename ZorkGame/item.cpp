#include "item.h"

// ----------------------------------------------------
Item::Item(const char* name, const char* description, Room* room, ItemType itemType, Entity* container) :
	Entity(name, description, (Entity*)room), container(container)
{
	type = ITEM;
	item_type = itemType;
	attack_power = 0;
	defense_power = 0;
	heal_power = 0;
	opened = true;
	canTake = true;
	key = NULL;
	child = NULL;
	appear = true;
	locked = false;
	room->elements.push_back(this);
	if (container != NULL) {
		container->child = this;
		if (container->type == CREATURE) {
			Creature* cr = (Creature*)container;
			cr->inventory = this;
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
			Item* it = (Item*)container;
			return it->opened;
		}
		
	}

	return true;
}

// ----------------------------------------------------

void Item::Look() const {

	if (ContainerIsOpened() && container != NULL) {
		cout << "\n" << name << "\n";
		cout << "It's in the " << container->name << ".\n";
	}
	else if(opened && child != NULL) {
		cout << "\n" << name << "\n";
		cout << "There is a "<< child->name << " inside...\n";
	}
	else {
		cout << "\n" << name << "\n";
		cout << description << "\n";
	}
}




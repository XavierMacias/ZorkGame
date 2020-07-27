#include "item.h"

// ----------------------------------------------------
Item::Item(const char* name, const char* description, Room* room, ItemType itemType, Item* container) :
	Entity(name, description, (Entity*)room), container(container)
{
	type = ITEM;
	item_type = itemType;
	attack_power = 0;
	defense_power = 0;
	heal_power = 0;
	opened = true;
	canTake = true;
	child = NULL;
	room->elements.push_back(this);
	if (container != NULL) {
		container->child = this;
	}
	
	//if (one_way == false)
	//	destination->container.push_back(this);
}

// ----------------------------------------------------
Item::~Item()
{
}
// ----------------------------------------------------
bool Item::ContainerIsOpened() const {
	if (container != NULL) {
		return container->opened;
	}

	return true;
}

// ----------------------------------------------------

void Item::Look() const {

	if (ContainerIsOpened() && container != NULL) {
		cout << "\n" << name << "\n";
		cout << "It is inside the " << container->name << ".\n";
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




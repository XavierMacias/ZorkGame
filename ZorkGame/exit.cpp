#include <iostream>
#include "exit.h"

// ----------------------------------------------------
Exit::Exit(const char* direction, const char* lead, const char* description, Room* origin, Room* destination) :
	Entity(direction, description, (Entity*)origin),
	locked(false), destination(destination), lead(lead), key(NULL), direction(direction), origin(origin)
{
	type = EXIT;
	origin->elements.push_back(this);
	destination->elements.push_back(this);
	//if (one_way == false)
	//	destination->container.push_back(this);
}

// ----------------------------------------------------
Exit::~Exit()
{
}

// ----------------------------------------------------
void Exit::Look(int isOrigin) const
{
	//cout << name << " to " << opposite_name << "\n";
	//cout << description << "\n";
	if (isOrigin == 0) {
		cout << "In direction " << direction << " there is a " << description << " that leads to a " << destination->name << ".\n";
	}
	else {
		cout << "In direction " << lead << " there is a " << description << " that leads to a " << origin->name << ".\n";
	}
	
}

// ----------------------------------------------------
/*const string& Exit::GetNameFrom(const Room* room) const
{
	//if (room == parent)
	//	return name;
	if (room == destination)
		return opposite_name;

	return name; // error ?
}

// ----------------------------------------------------
Room* Exit::GetDestinationFrom(const Room* room) const
{
	//if (room == parent)
	//	return destination;
	//if (room == destination)
	//	return (Room*)parent;

	return NULL;
}*/
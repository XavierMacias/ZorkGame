#include <iostream>
#include "exit.h"

// ----------------------------------------------------
Exit::Exit(const char* direction, const char* lead, const char* description, Room* origin, Room* destination) :
	Entity(direction, description, (Entity*)origin),
	locked(false), destination(destination), lead(lead), key(NULL), direction(direction), origin(origin)
{
	type = EXIT;
	origin->elements.push_back(this); // the room of origin add this exit to its elements.
	destination->elements.push_back(this); // the room of destination add this exit to its elements also. 
}

// ----------------------------------------------------
Exit::~Exit()
{
}

// ----------------------------------------------------
void Exit::Look(int isOrigin) const
{
	// depending of the point of view the directions change.
	if (isOrigin == 0) {
		cout << "In direction " << direction << " there is a " << description << " that leads to a " << destination->name << ".\n";
	}
	else {
		cout << "In direction " << lead << " there is a " << description << " that leads to a " << origin->name << ".\n";
	}
	
}
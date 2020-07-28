#include "entity.h"

// ----------------------------------------------------
Entity::Entity(const char* name, const char* description, Entity* room) :
	name(name), description(description), room(room)
{
	type = ENTITY;
	child = NULL; // if one item or creature have something inside it (like a chest with a key inside)

}

// ----------------------------------------------------
Entity::~Entity()
{}

// ----------------------------------------------------
void Entity::Look() const
{
	cout << name << "\n";
	cout << description << "\n";
}

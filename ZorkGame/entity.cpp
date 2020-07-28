#include "entity.h"

// ----------------------------------------------------
Entity::Entity(const char* name, const char* description, Entity* room) :
	name(name), description(description), room(room)
{
	type = ENTITY;
	child = NULL;

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

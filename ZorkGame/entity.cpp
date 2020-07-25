#include "entity.h"

// ----------------------------------------------------
Entity::Entity(const char* name, const char* description) :
	name(name), description(description)
{
	type = ENTITY;

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

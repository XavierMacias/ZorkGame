#ifndef __Entity__
#define __Entity__
#pragma once

#include <string>
#include <list>
#include <iostream>

using namespace std;

enum EntityType
{
	ENTITY,
	ROOM,
	EXIT,
	ITEM,
	CREATURE,
	NPC,
	PLAYER
};

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* room);
	virtual ~Entity();

	virtual void Look() const;

public:
	EntityType type;
	string name;
	string description;

	Entity* room;
};

#endif 


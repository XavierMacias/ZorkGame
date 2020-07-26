#pragma once
#ifndef __Room__
#define __Room__
#include <string>
#include <list>
#include "entity.h"
#include "creature.h"
#include "item.h"

class Entity;

using namespace std;

class Room : public Entity
{
	public:
		Room(const char* name, const char* description);
		~Room();

		void Look() const;

		//Exit* GetExit(const string& direction) const;

	public:
		list<Entity*> elements;
};
#endif


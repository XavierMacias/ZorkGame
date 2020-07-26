#pragma once
#include <string>
#include <list>
#include "entity.h"

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


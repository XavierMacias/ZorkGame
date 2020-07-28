#pragma once
#ifndef __Exit__
#define __Exit__
#include <string>
#include "entity.h"
#include "room.h"

using namespace std;

class Entity;
class Room;

class Exit : public Entity
{
	public:
		Exit(const char* direction, const char* lead, const char* description, Room* origin, Room* destination);
		~Exit();

		void Look(int isOrigin) const;

	public:
		const char* direction;
		bool locked;
		const char* lead;
		Room* destination;
		Room* origin;
		Entity* key;
};
#endif


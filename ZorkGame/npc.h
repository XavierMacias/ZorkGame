#pragma once
#ifndef __Npc__
#define __Npc__
#include "creature.h"

using namespace std;

class Npc : public Creature
{
	public:
		Npc(const char* name, const char* description, Room* room);
		~Npc();
};
#endif


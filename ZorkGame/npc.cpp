#include <iostream>
#include "npc.h"

using namespace std;

// ----------------------------------------------------
Npc::Npc(const char* name, const char* description, Room* room) :
	Creature(name, description, room, 1)
{
	type = NPC;

}

// ----------------------------------------------------
Npc::~Npc()
{
}

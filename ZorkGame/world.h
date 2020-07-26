#pragma once
#ifndef __World__
#define __World__
#include <vector>
#include "player.h"

class Player;

class World
{
public:

	World();
	~World();

	list<Entity*> GetEntitites();
	void LookInitialMap();
	bool CheckInstruction(vector<string> instr);

private:

	list<Entity*> entities;
	Player* player;
};

#endif


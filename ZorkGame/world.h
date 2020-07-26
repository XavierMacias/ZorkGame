#pragma once
#include <vector>
#include "player.h"

class World
{
public:

	World();
	~World();

	void LookInitialMap();
	bool CheckInstruction(vector<string> instr);

private:

	list<Entity*> entities;
	Player* player;
};


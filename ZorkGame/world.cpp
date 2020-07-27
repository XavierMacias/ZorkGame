#include <string>

#include "world.h"
#include "room.h"
#include "exit.h"
#include "creature.h"
#include "item.h"

using namespace std;

// ----------------------------------------------------
World::World()
{

	// Rooms ----
	Room* forest = new Room("Forest", "You are surrounded by tall trees. It feels like a huge forest someone could get lost easily.\n");
	Room* house = new Room("House", "You are inside a beautiful but small white house.\n");
	Room* basement = new Room("Basement", "The basement features old furniture and dim light.\n");

	Exit* ex1 = new Exit("west", "east", "little path", house, forest);
	Exit* ex2 = new Exit("south", "north", "stairs", house, basement);
	ex2->locked = true;

	entities.push_back(forest);
	entities.push_back(house);
	entities.push_back(basement);

	//entities.push_back(ex1);
	//entities.push_back(ex2);

	// Creatures ----
	Creature* butler = new Creature("Butler", "It's James, the house Butler.\n", house);
	//butler->hit_points = 10;
	entities.push_back(butler);

	// Items -----
	Item* mailbox = new Item("Mailbox", "Looks like it might contain something.\n", house, COMMON);
	Item* key = new Item("Key", "Old iron key.\n", basement, COMMON);
	//ex2->key = key;

	Item* sword = new Item("sword", "A simple old and rusty sword.\n", forest, WEAPON);
	sword->attack_power = 5;

	entities.push_back(mailbox);
	entities.push_back(sword);

	// Player ----
	player = new Player("Hero", "You are an awesome adventurer!\n", forest);
	entities.push_back(player);
}

// ----------------------------------------------------
World::~World()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete* it;

	entities.clear();
}
// ----------------------------------------------------
list<Entity*> World::GetEntitites() {
	return entities;
}
// ----------------------------------------------------
void World::LookInitialMap() {
	player->room->Look();
}
// ----------------------------------------------------
bool World::CheckInstruction(vector<string> instr) {
	//cout << instr << endl;
	string action = instr.at(0);
	if (instr.size() == 1) { // commands without arguments
		if (action == "help") {
			cout << "The possible commands are: help, inventory, go <direction>, look <something>, take <item>, drop <item>, attack <enemy>, open <item>, equip <weapon/armor>, unequip <weapon/armor>, use <item>, exit\n";
			return true;
		}
		else if (action == "inventory") {
			player->Inventory();
			return true;
		}
	}
	if (instr.size() == 2) { // commands with 1 argument
		
		string parameter = instr.at(1);
		if (action == "go") {
			Room* newRoom = player->Go(parameter);
			if (newRoom != NULL) {
				newRoom->Look();
			}
			return true;
		}
		else if (action == "look") {
			// parameter -> look
			return true;
		}
		else if (action == "take") {
			player->Take(parameter);
			return true;
		}
		else if (action == "drop") {
			player->Drop(parameter);
			return true;
		}
		else if (action == "attack") {
			// player -> attack parameter
			return true;
		}
		else if (action == "open") {
			// parameter -> open
			return true;
		}
		else if (action == "equip") {
			player->Equip(parameter);
			return true;
		}
		else if (action == "unequip") {
			player->Unequip(parameter);
			return true;
		}
		else if (action == "use") {
			// player -> use parameter
			return true;
		}

	}
	return false;
}
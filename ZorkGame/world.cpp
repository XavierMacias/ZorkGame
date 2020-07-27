#include <string>

#include "world.h"
#include "room.h"
#include "exit.h"
#include "creature.h"
#include "npc.h"
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
	Creature* butler = new Creature("guardian", "It's James, the house guardian.\n", house, 15);
	butler->text = "I'm the guardian of this house, you must defeat me.\n";
	//butler->hit_points = 10;
	entities.push_back(butler);

	// NPCs ----
	Npc* harry = new Npc("harry", "It's your friend Harry.", forest);
	harry->text = "Hello, to win the game you must defeat the ogre hidden somewhere in the map.\n";

	entities.push_back(harry);

	// Items -----
	Item* chest = new Item("chest", "A simple chest made of copper.\n", basement, COMMON);
	chest->opened = false;
	chest->canTake = false;
	Item* potion = new Item("potion", "A medicine to heal wounds.\n", house, HEALTH);
	potion->heal_power = 20;
	Item* key = new Item("key", "Old iron key.\n", house, COMMON);
	ex2->key = key;

	Item* sword = new Item("sword", "A simple old and rusty sword.\n", forest, WEAPON);
	sword->attack_power = 5;

	Item* shield = new Item("shield", "An old and rusty shield.\n", basement, ARMOUR, chest);
	shield->defense_power = 3;

	entities.push_back(chest);
	entities.push_back(key);
	entities.push_back(potion);
	entities.push_back(sword);
	entities.push_back(shield);

	// Player ----
	player = new Player("Hero", "You are an awesome adventurer!\n", forest, 30);
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
			player->Look(parameter);
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
			player->Attack(parameter);
			return true;
		}
		else if (action == "open") {
			player->Open(parameter);
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
			player->Use(parameter);
			return true;
		}
		else if (action == "talk") {
			player->Talk(parameter);
			return true;
		}

	}
	return false;
}
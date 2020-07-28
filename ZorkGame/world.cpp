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
	Room* field = new Room("Field", "You are in a huge open field with some trees.\n");
	Room* hill = new Room("Hill", "You are in a beautiful hill. There are some mountains on the horizon.\n");
	Room* forest = new Room("Forest", "You are in a creepy forest surrounded by tall trees.\n");
	Room* valley = new Room("Valley", "You are in a valley between two imponent mountains.\n");
	Room* grove = new Room("Grove", "A friendly grove sorrounded by little trees.\n");
	Room* cave = new Room("Cave", "A dark and sinister cave. You have a bad feeling.\n");
	Room* mountain = new Room("Mountain", "An enormous and steep mountain.\n");
	Room* mine = new Room("Mine", "An old and abandoned mine. It seems to be the end.\n");

	// Exits ----
	Exit* ex1 = new Exit("north", "south", "little path", field, hill);
	Exit* ex2 = new Exit("east", "west", "leafy road", field, forest);
	Exit* ex3 = new Exit("south", "north", "way down", forest, valley);
	Exit* ex4 = new Exit("west", "east", "little road", valley, grove);
	Exit* ex5 = new Exit("south", "north", "cave entrance", valley, cave);
	Exit* ex6 = new Exit("east", "west", "steep path", valley, mountain);
	Exit* ex7 = new Exit("south", "north", "mine entrance", mountain, mine);
	ex7->locked = true;

	entities.push_back(field);
	entities.push_back(hill);
	entities.push_back(forest);
	entities.push_back(valley);
	entities.push_back(grove);
	entities.push_back(cave);
	entities.push_back(mountain);
	entities.push_back(mine);

	entities.push_back(ex1);
	entities.push_back(ex2);
	entities.push_back(ex3);
	entities.push_back(ex4);
	entities.push_back(ex5);
	entities.push_back(ex6);
	entities.push_back(ex7);

	// Creatures ----
	Creature* wolf = new Creature("wolf", "It's a forest wolf.\n", forest, 10);
	wolf->text = "WOOF! WOOF!.\n";
	Creature* orc = new Creature("orc", "It's an evil orc.\n", cave, 10);
	orc->text = "You must defeat me if you want my treasures.\n";
	orc->attack = 2;
	Creature* ogre = new Creature("ogre", "It's an enormous and creepy ogre.\n", mine, 30);
	ogre->text = "I am the most powerful creature in the world. If you want the sacred star you must defeat me.\n";
	ogre->attack = 7;
	ogre->defense = 3;
	
	entities.push_back(wolf);
	entities.push_back(orc);
	entities.push_back(ogre);

	// NPCs ----
	Npc* harry = new Npc("harry", "It's your friend Harry.", field);
	harry->text = "Hello, to win the game you must use the sacred star hidden somewhere in the map.\n";

	Npc* warrior = new Npc("warrior", "It's an experimented warrior.", valley);
	warrior->text = "To defeat some enemies, you will need a weapon, like a sword.\n";
	
	Npc* hiker = new Npc("hiker", "A hiker that is exploring this mountain.", mountain);
	hiker->text = "Maybe some creature has the sacred star with it. Then you must defeat it to win.\n";

	entities.push_back(harry);
	entities.push_back(warrior);
	entities.push_back(hiker);

	// Items -----
	Item* chest = new Item("chest", "A simple chest made of copper.\n", hill, COMMON);
	chest->opened = false;
	chest->canTake = false;
	chest->locked = true;

	Item* box = new Item("box", "A small box made of wood.\n", grove, COMMON);
	box->opened = false;
	box->canTake = false;

	Item* potion = new Item("potion", "A medicine to heal wounds.\n", mountain, HEALTH);
	potion->heal_power = 30;

	Item* key = new Item("key", "Old iron key.\n", cave, COMMON, orc);
	ex7->key = key;
	Item* chestkey = new Item("chestkey", "A little key that open a chest", grove, COMMON, box);
	chest->key = chestkey;

	Item* sword = new Item("sword", "A simple old and rusty sword.\n", valley, WEAPON);
	sword->attack_power = 5;

	Item* shield = new Item("shield", "An old and rusty shield.\n", cave, ARMOUR);
	shield->defense_power = 3;
	orc->SetArmour(shield);

	Item* bigsword = new Item("bigSword", "A powerful and majestic sword.\n", hill, WEAPON, chest);
	bigsword->attack_power = 15;

	Item* star = new Item("star", "The sacred star that grant wishes and power.\n", mine, STAR, ogre);

	entities.push_back(chest);
	entities.push_back(key);
	entities.push_back(chestkey);
	entities.push_back(potion);
	entities.push_back(sword);
	entities.push_back(shield);
	entities.push_back(box);
	entities.push_back(bigsword);
	entities.push_back(star);

	// Player ----
	player = new Player("Hero", "You are an awesome adventurer!\n", field, 30);
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
	player->room->Look(); // description of the initial map
}
// ----------------------------------------------------
bool World::CheckInstruction(vector<string> instr) {
	string action = instr.at(0);
	if (instr.size() == 1) { // commands without arguments
		if (action == "help") {
			cout << "The possible commands are: help, inventory, go <direction>, look <something>, take <item>, drop <item>, attack <enemy>, open <item>, equip <weapon/armor>, unequip <weapon/armor>, loot <enemy>, use <item>, use <item> <direction/item>, exit\n";
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
		else if (action == "loot") {
			player->Loot(parameter);
			return true;
		}

	}
	if (instr.size() == 3) { // commands with 2 arguments
		string parameter = instr.at(1);
		string parameter2 = instr.at(2);
		if (action == "use") {
			player->Unlock(parameter, parameter2);
			return true;
		}
	}
	return false;
}
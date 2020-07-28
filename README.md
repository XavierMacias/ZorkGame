# ZorkGame

The author of this game is Xavier Macias Xicola. The game contains 8 rooms, and the player starts in the Field. The objective is get the sacred star and use it to win the game.
The posible commands are:
 - help: show you the possible commands to use
 - inventory: show you the items you have, the weapon and armour equiped, and the HP, attack and defense of the player.
 - go <direction>: move player to <direction> if it cans.
 - look <something>: get information about a Creature, NPC or object in the room.
 - take <item>: take item in the room and put in the player's inventory.
 - drop <item>: drop one item of the player's inventory and put in the actual room.
 - attack <enemy>: attack one enemy in the room.
 - talk <something>: you can talk with enemies or NPCs to obtain information.
 - open <item>: open one item in the room that can be opened (like a chest).
 - equip <weapon/armour>: equip one weapon or armour that the player has in it inventory.
 - unequip <weapon/armour>: unequip one weapon or armour that the player has equiped an return it to the inventory.
 - loot <enemy>: take the the objects that one enemy drops when it dies.
 - use <item>: use one item in the moment, like a potion or the sacred star.
 - use <item> <direction/item>: use one item (usually a key) in order to unlock another item or a path.
 - exit: exit the game.
  
The code is comented and I created some classes, one called: Entity, that is the parent of all the things you can find in the game: Room, Exit, Item, Creature, NPC, Player.
Creature is the parent of NPC and Player. There are the class: World, that defines and creates all the elements of the world, and the main, obviously.

To win the game, starting in Field (an NPC called harry will told you the objective if you talk with him, talk harry), you must to go to the east (forest, go east),
here you can find a wolf (optional enemy, you can attack it with "attack wolf"), and then you must go to the south (valley, go south). Here you must take the sword (take sword)
and equip it (equip sword). Then you can go to the south (go south) and attack the orc that is in the cave (attack orc) since kill it, and then you must loot it (loot orc).
After loot the orc you will obtain a shield (equip shield) and a key. Go north to return to the valley, and you can go west into the grove. Here there is a box, you can open
the box (open box) and then you can take the chestkey (take chestkey) that is inside the box. If you return to the field an go to the north, you can use the chestkey
(use chestkey chest) to open a chest and get a largeSword (first do: unequip sword, and then: equip largeSword) that give you more attack (check it using: inventory).
Finally, return to the valley, go to east (mountain), take a potion (take potion) and use it to recover health (use potion). Finally, you must use the key to
open the south path (use key south) and then you can go south, and you will find an ogre. Attack it (attack ogre) since it deads, so you can do: loot ogre in order to obtain 
the star. Finally do: use star, and you will win the game.

As a summary, the sorted commands to win are:
go east, go south, take sword, equip sword, go south, attack orc (since it deads), loot orc, equip shield, go north, go west, open box, take chestkey, go east, go north, go west, go north, use chestkey chest, open chest, take bigSword, unequip sword, equip bigSword, go south, go east, go south, go east, take potion, use potion, use key south,
go south, attack ogre (since it deads), loot ogre, use star.

#include "datastruct.h"
#include "data.h"

void data(vector<Items> &items, vector<Monsters> &monsters)
{
	// ----- STARTING EQ -----
	items.push_back(Items(items.size()+1, 0, 1, 0, 0, 0, 0, 100, COMBAT, "Knife"));
	items.push_back(Items(items.size()+1, 0, 0, 0, 5, 0, 0, 100, FOOD, "Bread"));
	
	// ----- COMBAT ITEMS -----
	//		----- Swords -----
	//							 		  fortuity, att, def, HPcure, from, len, rarity
	items.push_back(Items(items.size()+1, 1, 1, 0, 0, 1, 1, EPIC, COMBAT, "Staff"));
	items.push_back(Items(items.size()+1, 1, 1, 0, 0, 2, 1, COMMON, COMBAT, "Staff"));
	items.push_back(Items(items.size()+1, 1, 1, 0, 0, 3, 1, COMMON, COMBAT, "Staff"));

	items.push_back(Items(items.size()+1, 0, 3, 0, 0, 3, 1, UNCOMMON, COMBAT, "Short Sword"));
	items.push_back(Items(items.size()+1, 0, 3, 0, 0, 4, 1, UNCOMMON, COMBAT, "Short Sword"));
	items.push_back(Items(items.size()+1, 0, 3, 0, 0, 5, 1, COMMON, COMBAT, "Short Sword"));

	items.push_back(Items(items.size()+1, 1, 2, 0, 0, 3, 1, COMMON, COMBAT, "Sword"));
	items.push_back(Items(items.size()+1, 3, 7, 0, 0, 0, 1, COMMON, COMBAT, "Sun Sword"));

	//		----- Axes -----
	items.push_back(Items(items.size()+1, 3, 0, 0, 0, 0, 0, COMMON, COMBAT, "Axe"));
	items.push_back(Items(items.size()+1, 2, 2, 0, 0, 0, 0, COMMON, COMBAT, "Hand Axe"));
	items.push_back(Items(items.size()+1, 4, 1, 0, 0, 0, 0, COMMON, COMBAT, "Steel Axe"));

	//		----- Distance -----
	items.push_back(Items(items.size()+1, 1, 3, 0, 0, 7, 2, COMMON, COMBAT, "Snakebite Rod"));
	items.push_back(Items(items.size()+1, 2, 5, 0, 0, 8, 2, COMMON, COMBAT, "Wand of Vortex"));
	items.push_back(Items(items.size()+1, 3, 7, 0, 0, 9, 2, COMMON, COMBAT, "Wand of Inferno"));

	//		----- Armors -----
	items.push_back(Items(items.size()+1, 0, 0, 2, 0, 2, 3, COMMON, ARMOR, "Leather Armor"));
	items.push_back(Items(items.size()+1, 2, 0, 5, 0, 6, 3, COMMON, ARMOR, "Chain Armor"));

	//		----- Legs -----
	items.push_back(Items(items.size()+1, 0, 0, 2, 0, 3, 3, COMMON, LEGS, "Leather Legs"));
	items.push_back(Items(items.size()+1, 1, 0, 4, 0, 7, 3, COMMON, LEGS, "Chain Legs"));	

	//		----- Helmet -----
	items.push_back(Items(items.size()+1, 0, 0, 3, 0, 4, 2, COMMON, HELMET, "Studden Helmet"));
	items.push_back(Items(items.size()+1, 1, 0, 5, 0, 8, 3, COMMON, HELMET, "Legion Helmet"));	

	//		----- Boots -----
	items.push_back(Items(items.size()+1, 1, 0, 1, 0, 2, 2, COMMON, BOOTS, "Leather Boots"));
	items.push_back(Items(items.size()+1, 5, 0, 3, 0, 6, 4, COMMON, BOOTS, "Steel Boots"));

	//		----- Shields -----
	items.push_back(Items(items.size()+1, 0, 0, 2, 0, 4, 3, COMMON, SHIELD, "Wooden Shield"));
	items.push_back(Items(items.size()+1, 1, 0, 6, 0, 8, 3, COMMON, SHIELD, "Brass Shield"));

	// ----- FOOD ITEMS -----
	items.push_back(Items(items.size()+1, 0, 0, 0, 1, 1, 3, COMMON, FOOD, "Blueberry"));

	items.push_back(Items(items.size()+1, 1, 0, 0, 2, 3, 10, COMMON, FOOD, "Apple"));
	items.push_back(Items(items.size()+1, 3, 0, 0, 3, 3, 10, COMMON, FOOD, "Bread"));

	// ----- FINISH ITEM -----
	items.push_back(Items(items.size()+1, 0, 0, 0, 0, 0, 0, 0, GOAL, "Escape Key!"));

		

	// ----- MONSTERS -----
	//									  		   lvl, att, def, hp, exp, from, len, rarity
	monsters.push_back(Monsters(monsters.size()+1, 1, 1, 1, 5, 10, 1, 1, SCOMMON, "Rat"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 1, 1, 5, 10, 1, 1, SCOMMON, "Rat"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 1, 1, 5, 10, 2, 1, COMMON, "Rat"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 1, 1, 5, 10, 3, 2, RARE, "Rat"));

	monsters.push_back(Monsters(monsters.size()+1, 1, 2, 2, 3, 13, 2, 1, COMMON, "Bat"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 2, 2, 3, 13, 3, 1, SCOMMON, "Bat"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 2, 2, 3, 13, 4, 2, COMMON, "Bat"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 2, 2, 3, 13, 4, 2, UNCOMMON, "Bat"));

	monsters.push_back(Monsters(monsters.size()+1, 1, 2, 2, 7, 17, 3, 1, COMMON, "Spider"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 2, 2, 7, 17, 3, 1, COMMON, "Spider"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 2, 2, 7, 17, 4, 1, COMMON, "Spider"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 2, 2, 7, 17, 4, 1, COMMON, "Spider"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 2, 2, 7, 17, 5, 2, UNCOMMON, "Spider"));
	monsters.push_back(Monsters(monsters.size()+1, 1, 2, 2, 7, 17, 5, 2, UNCOMMON, "Spider"));

	monsters.push_back(Monsters(monsters.size()+1, 2, 2, 2, 7, 20, 4, 3, COMMON, "Snake"));
	monsters.push_back(Monsters(monsters.size()+1, 2, 2, 2, 7, 20, 4, 3, COMMON, "Snake"));
	monsters.push_back(Monsters(monsters.size()+1, 2, 2, 2, 7, 20, 4, 3, COMMON, "Snake"));

	monsters.push_back(Monsters(monsters.size()+1, 0, 4, 2, 10, 30, 5, 3, COMMON, "Poison Spider"));
	monsters.push_back(Monsters(monsters.size()+1, 0, 4, 2, 10, 30, 5, 3, COMMON, "Poison Spider"));
	monsters.push_back(Monsters(monsters.size()+1, 0, 4, 2, 10, 30, 5, 3, COMMON, "Poison Spider"));

	monsters.push_back(Monsters(monsters.size()+1, 3, 2, 2, 15, 25, 5, 3, COMMON, "Troll"));
	monsters.push_back(Monsters(monsters.size()+1, 3, 2, 2, 15, 25, 5, 3, COMMON, "Troll"));
	monsters.push_back(Monsters(monsters.size()+1, 3, 2, 2, 15, 25, 5, 3, COMMON, "Troll"));

	monsters.push_back(Monsters(monsters.size()+1, 5, 2, 2, 20, 30, 6, 3, COMMON, "Orc"));
	monsters.push_back(Monsters(monsters.size()+1, 5, 2, 2, 20, 30, 6, 3, COMMON, "Orc"));
	monsters.push_back(Monsters(monsters.size()+1, 5, 2, 2, 20, 30, 6, 3, COMMON, "Orc"));

	monsters.push_back(Monsters(monsters.size()+1, 8, 3, 5, 30, 32, 7, 2, COMMON, "Troll Guard"));
	monsters.push_back(Monsters(monsters.size()+1, 8, 3, 5, 30, 32, 7, 2, COMMON, "Troll Guard"));

	monsters.push_back(Monsters(monsters.size()+1, 10, 4, 4, 30, 35, 8, 3, COMMON, "Skeleton"));
	monsters.push_back(Monsters(monsters.size()+1, 10, 4, 4, 30, 35, 8, 3, COMMON, "Skeleton"));
	monsters.push_back(Monsters(monsters.size()+1, 10, 4, 4, 30, 35, 8, 3, COMMON, "Skeleton"));

	monsters.push_back(Monsters(monsters.size()+1, 5, 7, 3, 30, 40, 9, 3, COMMON, "Orc Warrior"));
	monsters.push_back(Monsters(monsters.size()+1, 5, 7, 3, 30, 40, 9, 3, COMMON, "Orc Warrior"));
	monsters.push_back(Monsters(monsters.size()+1, 5, 7, 3, 30, 40, 9, 3, COMMON, "Orc Warrior"));

	monsters.push_back(Monsters(monsters.size()+1, 5, 5, 5, 40, 45, 10, 2, COMMON, "Minotaur"));
	monsters.push_back(Monsters(monsters.size()+1, 5, 5, 5, 40, 45, 10, 2, COMMON, "Minotaur"));
	monsters.push_back(Monsters(monsters.size()+1, 5, 5, 5, 40, 45, 10, 2, COMMON, "Minotaur"));
	monsters.push_back(Monsters(monsters.size()+1, 5, 5, 5, 40, 45, 10, 2, COMMON, "Minotaur"));

	monsters.push_back(Monsters(monsters.size()+1, 7, 4, 7, 45, 50, 11, 3, COMMON, "Ice Golem"));
	monsters.push_back(Monsters(monsters.size()+1, 7, 4, 7, 45, 50, 11, 3, COMMON, "Ice Golem"));
	monsters.push_back(Monsters(monsters.size()+1, 7, 4, 7, 45, 50, 11, 3, COMMON, "Ice Golem"));

	monsters.push_back(Monsters(monsters.size()+1, 7, 7, 5, 50, 60, 12, 3, COMMON, "Fire Elemental"));
	monsters.push_back(Monsters(monsters.size()+1, 7, 7, 5, 50, 60, 12, 3, COMMON, "Fire Elemental"));
	monsters.push_back(Monsters(monsters.size()+1, 7, 7, 5, 50, 60, 12, 3, COMMON, "Fire Elemental"));

	monsters.push_back(Monsters(monsters.size()+1, 8, 6, 6, 60, 70, 13, 3, COMMON, "Efreet"));
	monsters.push_back(Monsters(monsters.size()+1, 8, 6, 6, 60, 70, 13, 3, COMMON, "Efreet"));
	monsters.push_back(Monsters(monsters.size()+1, 8, 6, 6, 60, 70, 13, 3, COMMON, "Efreet"));

	monsters.push_back(Monsters(monsters.size()+1, 9, 7, 7, 70, 80, 14, 3, COMMON, "Giant Spider"));
	monsters.push_back(Monsters(monsters.size()+1, 9, 7, 7, 70, 80, 14, 3, COMMON, "Giant Spider"));
	monsters.push_back(Monsters(monsters.size()+1, 9, 7, 7, 70, 80, 14, 3, COMMON, "Giant Spider"));

	monsters.push_back(Monsters(monsters.size()+1, 10, 8, 5, 80, 90, 15, 3, COMMON, "Dragon"));
	monsters.push_back(Monsters(monsters.size()+1, 10, 8, 5, 80, 90, 15, 3, COMMON, "Dragon"));
	monsters.push_back(Monsters(monsters.size()+1, 10, 8, 5, 80, 90, 15, 3, COMMON, "Dragon"));

	monsters.push_back(Monsters(monsters.size()+1, 11, 10, 7, 90, 100, 16, 3, COMMON, "Black Knight"));
	monsters.push_back(Monsters(monsters.size()+1, 11, 10, 7, 90, 100, 16, 3, COMMON, "Black Knight"));
	monsters.push_back(Monsters(monsters.size()+1, 11, 10, 7, 90, 100, 16, 3, COMMON, "Black Knight"));

	monsters.push_back(Monsters(monsters.size()+1, 12, 10, 10, 100, 110, 17, 3, COMMON, "Son of Verminor"));
	monsters.push_back(Monsters(monsters.size()+1, 12, 10, 10, 100, 110, 17, 3, COMMON, "Son of Verminor"));
	monsters.push_back(Monsters(monsters.size()+1, 12, 10, 10, 100, 110, 17, 3, COMMON, "Son of Verminor"));

	monsters.push_back(Monsters(monsters.size()+1, 13, 13, 10, 105, 120, 18, 3, COMMON, "Dragon Lord"));
	monsters.push_back(Monsters(monsters.size()+1, 13, 13, 10, 105, 120, 18, 3, COMMON, "Dragon Lord"));
	monsters.push_back(Monsters(monsters.size()+1, 13, 13, 10, 105, 120, 18, 3, COMMON, "Dragon Lord"));

	monsters.push_back(Monsters(monsters.size()+1, 15, 15, 15, 120, 130, 19, 3, COMMON, "Demon"));
	monsters.push_back(Monsters(monsters.size()+1, 15, 15, 15, 120, 130, 19, 3, COMMON, "Demon"));
	monsters.push_back(Monsters(monsters.size()+1, 15, 15, 15, 120, 130, 19, 3, COMMON, "Demon"));

}

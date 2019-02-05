#ifndef __DATASTRUCT_H_
#define __DATASTRUCT_H_

#include <iostream>
#include <vector>
#include <stdlib.h> // srand, rand
#include <time.h> // time as seed
//#include <windows.h>
//#include <conio.h>
#include <math.h>
#include <sstream>

#include <stdio.h>
#include <cstdio>

#include <unistd.h>
#include <termios.h>

#include <unistd.h>

using namespace std;

#define MAP_SIZE 11
#define GOAL_LEVEL 5

enum RoomType
{
	NOTHING = 0,
	NORMAL = 1,
	START = 2, // first level, first room
	FINISH = 3, // room where treasure lies
	UPSTAIRS = 4,
	DOWNSTAIRS = 5,
	HIDDEN = 6
};
enum ItemType
{
	COMBAT = 0,
	ARMOR = 1,
	LEGS = 2,
	HELMET = 3,
	BOOTS = 4,
	SHIELD = 5,
	FOOD = 6,
	GOAL = 7
};
enum Rarity
{
	SCOMMON = 90,
	COMMON = 75,
	UNCOMMON = 50,
	RARE = 25,
	EPIC = 7,
	LEGENDARY = 2
};

class Items
{
public:
	short int mID;

	int mFortuityfactor; // nu of dice to roll
	int mAttack;
	int mDefense;
	int mHPcure;

	int mRespfrom;
	int mResplen; // duration of resping in dungeon lvls
	int mRarity; // in %

	ItemType mItemtype;
	std::string mName;

	Items(short int, int, int, int, int, int, int, int, ItemType, string);
};

class Monsters
{
public:
	short int mID;

	int mLevel;
	int mAttack;
	int mDefense;
	int mHP;
	int mEXP;

	int mRespfrom;
	int mResplen;
	int mRarity;

	string mName;

	Monsters(short int, int, int, int, int, int, int, int, int, string);
};

class RoomContent
{
public:
	vector<int> mMonsters;
	vector<int> mItems;

	unsigned int mSelectedContent;
};

class LevelsStack
{
public:
    RoomType mArraymap[MAP_SIZE][MAP_SIZE];
    bool mSeenmap[MAP_SIZE][MAP_SIZE];
    int mnLevel; // member, number of level
    int mnRooms; // member, number of rooms

    RoomContent* mRoomcontent;

    LevelsStack* pNext;
    LevelsStack* pPrev;
    
    LevelsStack(int a, vector<Items> itemsBase, vector<Monsters> monstersBase); // konstruktor
    void computeNRooms(int nLevel, int max); // n of rooms
    void generateMap(int mapSize);
    void generateRoomsContent(bool generateItems, 
    	vector<Items> itemsBase, vector<Monsters> monstersBase);
    void displayRoomContent(int roomNumber, int heroCoorX, int heroCoorY, 
    	vector<Items> itemsBase, vector<Monsters> monstersBase);
    int computeRoomNumber(int heroCoorX, int heroCoorY);
};
void pushLevelsStack(LevelsStack** head, vector<Items> itemsBase, vector<Monsters> monstersBase);

class Hero
{
public:
	string mName;
	int mEXP;
	int mEXP4nextLVL;
	int mLVL;
	int mHP;
	// maxHP = lvl * 10

	string mDMG;
	string mDEF;

	int mCoorx;
	int mCoory;

	unsigned short int mMaxInvSize;

	vector<int> mEQ; // wearing stuff, 6 places
	vector<int> mInventory; // IDs inside

	unsigned int mSelectedItem;

	Hero(string mName);
	void setInitCoor(RoomType arrayMap[][MAP_SIZE], bool transistionType);
	void setStartingINV();
	void displayHeroItems(vector<Items> itemsBase);
	void displayStats(vector<Items> itemsBase);
	void mSetStringAttDef(vector<Items> itemsBase);
	bool fight(LevelsStack* levelsStack, vector<Items> itemsBase, vector<Monsters> monstersBase);
	void expManagement(int expToAdd);
	void addHP(int hpToAdd);
};



#endif // __DATASTRUCT_H_

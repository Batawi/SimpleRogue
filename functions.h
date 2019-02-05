#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#include "datastruct.h"

void gameLoop(); // main game loop
bool actions(Hero &hero, LevelsStack** levelsStack, 
	vector<Items> itemsBase, vector<Monsters> monstersBase); // executing key presses
void bordersDrawing();
void mapDrawing(Hero hero, LevelsStack levelsStack);
void listAllLevelContent(LevelsStack* levelsStackHead, 
	vector<Items> itemsBase, vector<Monsters> monstersBase);
void setCursor(short int x, short int y);
int diceRoller(int repetitions);
bool isItWearable(ItemType itemType);
bool isItDefensive(ItemType itemType);
bool isThereAnyMonster(LevelsStack* levelsStack, int roomNumber);
void eatOrEq(Hero &hero, vector<Items> itemsBase);
void stop(int nError);
void drawLabel(string s);
void youLose();
void youWin();
void clearInfoBox();
void displayInfoBox(vector<string> info);
void displayHelp();
bool checkWin(Hero hero, int lvlNumber, vector<Items> itemsBase);

void heroDmgDefSimulator();
void displayExpTable();

void gameMenu();
char getch();
#endif // __FUNCTIONS_H_

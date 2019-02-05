#include "functions.h"
#include "datastruct.h"
#include "data.h"


void gameLoop()
{
		srand (time(NULL));

		// heroDmgDefSimulator();

		vector<Items> itemsBase;
		vector<Monsters> monstersBase;
		data(itemsBase, monstersBase);


		bool endOfGame=0;

		LevelsStack* levelsStackHead=NULL;

		pushLevelsStack(&levelsStackHead, itemsBase, monstersBase);


		Hero hero("Batawi");
		hero.setInitCoor(levelsStackHead->mArraymap, 0);

		std::system("clear");
		while(endOfGame==0)
		{
			bordersDrawing();
			mapDrawing(hero, *levelsStackHead);

			levelsStackHead->displayRoomContent
			(levelsStackHead->computeRoomNumber(hero.mCoorx, hero.mCoory), hero.mCoorx, hero.mCoory, 
				itemsBase, monstersBase);

			hero.displayHeroItems(itemsBase);
			hero.displayStats(itemsBase);

			endOfGame = actions(hero, &levelsStackHead, itemsBase, monstersBase);
			std::system("clear");
		}


        std::cin.get();
}

bool actions(Hero &hero, LevelsStack** levelsStack, vector<Items> itemsBase, vector<Monsters> monstersBase)
{
	char in;
	in=getch();

	// ----- MOVING AROUND MAP -----
	if((in==(char)75 || in=='a') && hero.mCoorx-1>=0 &&
		!isThereAnyMonster(*levelsStack, (*levelsStack)->computeRoomNumber(hero.mCoorx, hero.mCoory)-1)) // left
	{
	    if((*levelsStack)->mArraymap[hero.mCoory][hero.mCoorx-1]!=NOTHING)
	    {
	        hero.mCoorx -= 1;
	        (*levelsStack)->mSeenmap[hero.mCoory][hero.mCoorx]=1;
	    }
	}
	else if((in==(char)77 || in=='d') && hero.mCoorx+1<=MAP_SIZE-1 &&
		!isThereAnyMonster(*levelsStack, (*levelsStack)->computeRoomNumber(hero.mCoorx, hero.mCoory)-1)) // right
	{
	    if((*levelsStack)->mArraymap[hero.mCoory][hero.mCoorx+1]!=NOTHING)
	    {
	        hero.mCoorx += 1;
	        (*levelsStack)->mSeenmap[hero.mCoory][hero.mCoorx]=1;
	    }
	}
	else if((in==(char)72 || in=='w') && hero.mCoory-1>=0 &&
		!isThereAnyMonster(*levelsStack, (*levelsStack)->computeRoomNumber(hero.mCoorx, hero.mCoory)-1)) // up
	{
	    if((*levelsStack)->mArraymap[hero.mCoory-1][hero.mCoorx]!=NOTHING)
	    {
	        hero.mCoory -= 1;
	        (*levelsStack)->mSeenmap[hero.mCoory][hero.mCoorx]=1;
	    }
	}
	else if((in==(char)80  || in=='s') && hero.mCoory+1<=MAP_SIZE-1 &&
		!isThereAnyMonster(*levelsStack, (*levelsStack)->computeRoomNumber(hero.mCoorx, hero.mCoory)-1)) // down
	{
	    if((*levelsStack)->mArraymap[hero.mCoory+1][hero.mCoorx]!=NOTHING)
	    {
	        hero.mCoory += 1;
	        (*levelsStack)->mSeenmap[hero.mCoory][hero.mCoorx]=1;
	    }
	}

	// ----- GO LV UP OR LV DOWN -----
	else if(in==' ') 
	{
		if((*levelsStack)->mArraymap[hero.mCoory][hero.mCoorx]==UPSTAIRS)
		{
			*levelsStack = (*levelsStack)->pPrev;
			(*levelsStack)->generateRoomsContent(0, itemsBase, monstersBase);
			hero.setInitCoor((*levelsStack)->mArraymap, 1);
		}
		else if((*levelsStack)->mArraymap[hero.mCoory][hero.mCoorx]==DOWNSTAIRS)
		{
			if((*levelsStack)->pNext!=NULL)
			{
				*levelsStack = (*levelsStack)->pNext;
				(*levelsStack)->generateRoomsContent(0, itemsBase, monstersBase);
			}
			else
			{
				pushLevelsStack(levelsStack, itemsBase, monstersBase);
			}
			hero.setInitCoor((*levelsStack)->mArraymap, 0);
		}
		else if((*levelsStack)->mArraymap[hero.mCoory][hero.mCoorx]==START)
		{
			if(checkWin(hero, (*levelsStack)->mnLevel, itemsBase))
			{
				youWin();
				return 1;
			}
		}
	}

	// ----- CURSOR MAP CONTENT -----
	else if(in=='r')
	{
		int roomNumber = 
			(*levelsStack)->computeRoomNumber(hero.mCoorx, hero.mCoory)-1;

		if((*levelsStack)->mRoomcontent[roomNumber].mSelectedContent > 1)
		{
			(*levelsStack)->mRoomcontent[roomNumber].mSelectedContent--;
		}
		else
		{
			(*levelsStack)->mRoomcontent[roomNumber].mSelectedContent = 
			(*levelsStack)->mRoomcontent[roomNumber].mMonsters.size() + 
			(*levelsStack)->mRoomcontent[roomNumber].mItems.size();
		}
	}
	else if(in=='f')
	{
		int roomNumber = 
			(*levelsStack)->computeRoomNumber(hero.mCoorx, hero.mCoory)-1;

		if((*levelsStack)->mRoomcontent[roomNumber].mSelectedContent <
			(*levelsStack)->mRoomcontent[roomNumber].mMonsters.size() + 
			(*levelsStack)->mRoomcontent[roomNumber].mItems.size())
		{
			(*levelsStack)->mRoomcontent[roomNumber].mSelectedContent++;
		}
		else
		{
			(*levelsStack)->mRoomcontent[roomNumber].mSelectedContent = 1;
		}
	}

	// ----- CURSOR HERO ITEMS -----
	else if(in=='j')
	{
		if(hero.mSelectedItem > 1)
		{
			hero.mSelectedItem--;
		}
		else
		{
			hero.mSelectedItem = hero.mInventory.size() + hero.mEQ.size();
		}
	}
	else if(in=='k')
	{
		if(hero.mSelectedItem < hero.mInventory.size() + hero.mEQ.size())
		{
			hero.mSelectedItem++;
		}
		else
		{
			hero.mSelectedItem = 1;
		}
	}

	// ----- INVADE / ATTACK -----
	else if(in=='i')
	{
		if(hero.fight(*levelsStack, itemsBase, monstersBase))
		{
			youLose();
			return 1;
		}
	}

	// ----- PICK UP -----
	else if(in=='p')
	{
		int roomNumber = 
			(*levelsStack)->computeRoomNumber(hero.mCoorx, hero.mCoory)-1;

		if((*levelsStack)->mRoomcontent[roomNumber].mSelectedContent >
			(*levelsStack)->mRoomcontent[roomNumber].mMonsters.size())
		{
			int a = (*levelsStack)->mRoomcontent[roomNumber].mSelectedContent -
			(*levelsStack)->mRoomcontent[roomNumber].mMonsters.size() - 1;

			if(hero.mInventory.size() < hero.mMaxInvSize)
			{
				hero.mInventory.push_back((*levelsStack)->mRoomcontent[roomNumber].mItems[a]);
				(*levelsStack)->mRoomcontent[roomNumber].mItems.erase(
					(*levelsStack)->mRoomcontent[roomNumber].mItems.begin() + a);

				if((*levelsStack)->mRoomcontent[roomNumber].mSelectedContent >= 
					(*levelsStack)->mRoomcontent[roomNumber].mMonsters.size() + 
					(*levelsStack)->mRoomcontent[roomNumber].mItems.size())
				{
					(*levelsStack)->mRoomcontent[roomNumber].mSelectedContent = 
					(*levelsStack)->mRoomcontent[roomNumber].mMonsters.size() + 
					(*levelsStack)->mRoomcontent[roomNumber].mItems.size();
				}
			}
		}
	}

	// ----- EAT / EQUIP -----
	else if(in=='e')
	{
		eatOrEq(hero, itemsBase);
	}

	// ----- LEAVE / THROW ITEM -----
	else if(in=='t')
	{
		int roomNumber = 
			(*levelsStack)->computeRoomNumber(hero.mCoorx, hero.mCoory)-1;
		int item_ID;

		if(hero.mSelectedItem > 0 &&
			hero.mSelectedItem <= hero.mEQ.size())
		{
			item_ID = hero.mEQ[hero.mSelectedItem-1];

			hero.mEQ.erase(hero.mEQ.begin() + hero.mSelectedItem - 1);
			(*levelsStack)->mRoomcontent[roomNumber].mItems.push_back(item_ID);
		}
		else if(hero.mSelectedItem > hero.mEQ.size() && 
			hero.mSelectedItem <= hero.mInventory.size() + hero.mEQ.size())
		{
			item_ID = hero.mInventory[hero.mSelectedItem - hero.mEQ.size()-1];

			hero.mInventory.erase(hero.mInventory.begin() + hero.mSelectedItem - hero.mEQ.size() - 1);
			(*levelsStack)->mRoomcontent[roomNumber].mItems.push_back(item_ID);
		}

		if(hero.mSelectedItem >= 
			hero.mEQ.size() + 
			hero.mInventory.size())
		{
			hero.mSelectedItem = 
			hero.mEQ.size() + 
			hero.mInventory.size();
		}
	}

	// ----- EXP TABLE -----
	else if(in=='m')
	{
		displayExpTable();
	}

	// ----- HELP -----
	else if(in=='?')
	{
		displayHelp();
	}

	// ----- EXIT -----
	else if(in==(char)27) // esc
	{
		vector<string> s;
		s.push_back("Exit for sure? (y / anything else)");
		displayInfoBox(s);

		in = getch();
		if(in == 'y' || in == 'Y')
		{
		    return 1;
		}
	}
	return 0;
}

void bordersDrawing()
{
	// --- LINES ---
	//	--- corners ---
	setCursor(0, 0);
	std::cout<<"|";
	setCursor(79, 0);
	std::cout<<"|";
	setCursor(0, 24);
	std::cout<<"|";
	setCursor(79, 24);
	std::cout<<"|";

	// --- main border ---
	for(int i=1; i<79; i++)
	{
		setCursor(i, 0);
		cout<<"=";
		setCursor(i, 20);
		cout<<"=";
		setCursor(i, 24);
		cout<<"=";
	}
	for(int i=1; i<24; i++)
	{
		setCursor(0, i);
		cout<<"|";
		setCursor(79, i);
		cout<<"|";
	}

	// --- triples --- 
	setCursor(0, 20);
	std::cout<<"|";
	setCursor(79, 20);
	std::cout<<"|";


	setCursor(25, 0);
	std::cout<<"=";
	setCursor(41, 0);
	std::cout<<"=";
	setCursor(66, 0);
	std::cout<<"=";

	setCursor(25, 20);
	std::cout<<"=";
	setCursor(41, 20);
	std::cout<<"=";
	setCursor(66, 20);
	std::cout<<"=";

	// --- another vertical lines ---
	for(int i=1; i<20; i++)
	{
		setCursor(25, i);
		cout<<"|";
		setCursor(41, i);
		cout<<"|";
		setCursor(66, i);
		cout<<"|";
	}

	for(int i=26; i<41; i++)
	{
		setCursor(i, 16);
		cout<<"=";
	}

	setCursor(25, 16);
	std::cout<<"|";
	setCursor(41, 16);
	std::cout<<"|";
}

void mapDrawing(Hero hero, LevelsStack levelsStack)
{
	short int mapSize = 5; // size of map to draw
/*	short int startingPointX = 1;
	short int startingPointY = 1;*/
	short int startingPointX = 26;
	short int startingPointY = 1;
	int k, m;


	for(int i=0; i<mapSize; i++) // y
	{
		k = hero.mCoory-mapSize/2+i;

		for(int j=0; j<mapSize; j++) // x
		{
			m = hero.mCoorx-mapSize/2+j;

			if(levelsStack.mSeenmap[k][m]==1)
			{
				// Corners
				setCursor(j*3+startingPointX, i*3+startingPointY);
				cout<<"/";
				setCursor(j*3+2+startingPointX, i*3+startingPointY);
				cout<<"\\";
				setCursor(j*3+startingPointX, i*3+2+startingPointY);
				cout<<"\\";
				setCursor(j*3+2+startingPointX, i*3+2+startingPointY);
				cout<<"/";
				// Walls
				setCursor(j*3+1+startingPointX, i*3+startingPointY);
				if(k-1>=0 && levelsStack.mArraymap[k-1][m]!=NOTHING && levelsStack.mArraymap[k-1][m]!=HIDDEN) // up check
				{
					cout<<".";
				}
				else cout<<"-";

				setCursor(j*3+1+startingPointX, i*3+2+startingPointY);
				if(k+1<=MAP_SIZE-1 && levelsStack.mArraymap[k+1][m]!=NOTHING && levelsStack.mArraymap[k+1][m]!=HIDDEN) // down check
				{
					cout<<".";
				}
				else cout<<"-";

				setCursor(j*3+startingPointX, i*3+1+startingPointY);
				if(m-1>=0 && levelsStack.mArraymap[k][m-1]!=NOTHING && levelsStack.mArraymap[k][m-1]!=HIDDEN) // left check
				{
					cout<<".";
				}
				else cout<<"|";

				setCursor(j*3+2+startingPointX, i*3+1+startingPointY);
				if(m+1<=MAP_SIZE-1 && levelsStack.mArraymap[k][m+1]!=NOTHING && levelsStack.mArraymap[k][m+1]!=HIDDEN) // right check
				{
					cout<<".";
				}
				else cout<<"|";
				// Letter
				setCursor(j*3+startingPointX+1, i*3+startingPointY+1);
				if(levelsStack.mArraymap[k][m]==UPSTAIRS)cout<<"U";
				else if(levelsStack.mArraymap[k][m]==DOWNSTAIRS) cout<<"D";
				else if(levelsStack.mArraymap[k][m]==START) cout<<"S";
				else if(levelsStack.mArraymap[k][m]==FINISH) cout<<"F";
				else if(levelsStack.mArraymap[k][m]==HIDDEN) cout<<"H";
				else cout<<" ";
			}
			// Clearing
			/*else
			{
				for(int p=0; p<3; p++)
				{
					for(int l=0; l<3; l++)
					{
						setCursor(l+j*3+startingPointX, p+i*3+startingPointY);
						cout<<" ";
					}
				}
			}*/
		}
	}

	// Hero draw
	setCursor(mapSize*3/2+startingPointX, mapSize*3/2+startingPointY);
	cout<<"@";
}

void listAllLevelContent(LevelsStack* levelsStackHead, vector<Items> itemsBase, vector<Monsters> monstersBase)
{
	setCursor(0, 15);
	for(int j=0; j<levelsStackHead->mnRooms; j++)
	{
		//cout<<endl<<"---------------";
		cout<<endl<<j+1<<" ITEMY ";
		for(unsigned int i=0; i<levelsStackHead->mRoomcontent[j].mItems.size(); i++)
		{
			cout<<endl<<itemsBase[(levelsStackHead->mRoomcontent[j].mItems[i]) - 1].mName;
		}

		cout<<endl<<j+1<<" POTWORY ";
		for(unsigned int i=0; i<levelsStackHead->mRoomcontent[j].mMonsters.size(); i++)
		{
			cout<<endl<<monstersBase[(levelsStackHead->mRoomcontent[j].mMonsters[i]) - 1].mName;
		}
	}
}

void setCursor(short int x, short int y)
{
    //COORD p = { x, y };
    //SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );

    std::cout << "\033[" << y+1 << ";" << x+1 << "H";
}

int diceRoller(int repetitions)
{
	int sum = 0;

	for(int i=0; i<repetitions; i++)
	{
		sum += rand()%3;
	}

	return sum; 
}

bool isItWearable(ItemType itemType)
{
	if(itemType == COMBAT || itemType == ARMOR ||
		itemType == LEGS || itemType == HELMET ||
		itemType == BOOTS || itemType == SHIELD)
	{
		return 1;
	}
	return 0;
}

bool isItDefensive(ItemType itemType)
{
	if(itemType == ARMOR || itemType == LEGS || itemType == HELMET ||
		itemType == BOOTS || itemType == SHIELD)
	{
		return 1;
	}
	return 0;
}

bool isThereAnyMonster(LevelsStack* levelsStack, int roomNumber)
{
	if((*levelsStack).mRoomcontent[roomNumber].mMonsters.empty())
	{
		return 0;
	}
	return 1;
}

void eatOrEq(Hero &hero, vector<Items> itemsBase)
{
	if(hero.mSelectedItem > 0 &&
		hero.mSelectedItem <= hero.mEQ.size())
	{
		if(hero.mInventory.size() < hero.mMaxInvSize)
		{
			hero.mInventory.push_back(hero.mEQ[hero.mSelectedItem-1]);
			hero.mEQ.erase(hero.mEQ.begin() + hero.mSelectedItem - 1);
		}
	}
	else if(hero.mSelectedItem > hero.mEQ.size() && 
		hero.mSelectedItem <= (hero.mInventory.size() + hero.mEQ.size()))
	{
		Items item = 
		itemsBase[hero.mInventory[hero.mSelectedItem-hero.mEQ.size()-1]-1];
		if(isItWearable(item.mItemtype))
		{
			bool alreadyWear = 0;
			for(unsigned int i=0; i<hero.mEQ.size(); i++)
			{
				if(itemsBase[hero.mEQ[i]-1].mItemtype == item.mItemtype)
				{
					//stop(0);
					int a = hero.mEQ[i];
					hero.mInventory.erase(hero.mInventory.begin() + hero.mSelectedItem-hero.mEQ.size()-1);
					hero.mEQ.erase(hero.mEQ.begin() + i);
					hero.mEQ.push_back(item.mID);
					hero.mInventory.push_back(a);

					i = hero.mEQ.size();
					alreadyWear = 1;
				}
			}

			if(alreadyWear == 0)
			{
				hero.mInventory.erase(hero.mInventory.begin() + hero.mSelectedItem-hero.mEQ.size()-1);
				// hero.mEQ.push_back(hero.mInventory[hero.mSelectedItem-hero.mEQ.size()-1]);
				hero.mEQ.push_back(item.mID);
			}
		}
		else if(item.mItemtype == FOOD)
		{
			if(hero.mHP < hero.mLVL*10)
			{
				hero.mInventory.erase(hero.mInventory.begin() + hero.mSelectedItem-hero.mEQ.size()-1);
				hero.addHP(item.mHPcure+diceRoller(item.mFortuityfactor));
			}
			else
			{
				vector<string> s;
				s.push_back("You are full!");
				displayInfoBox(s);
                std::cin.get();
			}

			if(hero.mSelectedItem >= 
				hero.mEQ.size() + 
				hero.mInventory.size())
			{
				hero.mSelectedItem = 
				hero.mEQ.size() + 
				hero.mInventory.size();
			}
		}
	}
}

void stop(int nError)
{
    setCursor(20, 15);
    std::cout<<"Program has been stopped with: "<<nError;
    std::cin.get();
    exit(0);
}

void drawLabel(string s)
{
	for(int i=0; i<5; i++)
	{
		cout<<"-";
	}
	cout<<" "<<s<<" ";
	for(int i=0; i<5; i++)
	{
		cout<<"-";
	}
}

void youLose()
{
	std::system("clear");
	setCursor(37, 12);
	cout<<"You lose";
    std::cin.get();
	exit(0);
}

void youWin()
{
	std::system("clear");
	setCursor(37, 12);
	cout<<"You Win";
    std::cin.get();
	exit(0);
}

void clearInfoBox()
{
	short int startingPointX = 1;
	short int startingPointY = 21;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<78; j++)
		{
			setCursor(startingPointX+j, startingPointY+i);
			cout<<" ";
		}
	}
}

void displayInfoBox(vector<string> info)
{
	clearInfoBox();

	if(info.size() >= 1)
	{
		setCursor(1, 23);
		cout<<info[info.size()-1];
	}
	if(info.size() >= 2)
	{
		setCursor(1, 22);
		cout<<info[info.size()-2];
	}
	if(info.size() >= 3)
	{
		setCursor(1, 21);
		cout<<info[info.size()-3];
	}
}

void displayHelp()
{
	std::system("clear");

	cout<<"HELP\n"
		<<"\n? - help window\n"
		<<"wsad - move around map\n"
		<<"space - go upstairs or downstairs \n"
		<<"rf - selecting map content\n"
		<<"jk - selecting inventory\n"
		<<"p - Pick up item\n"
		<<"t - Throw item\n"
		<<"e - eat / equip item\n"
		<<"i - attack\n"
		<<"s - skip fight\n"
		<<"esc - exit\n"
		<<"M - experience table\n"
		<<"\nYou were traped in the ancient dungeon,\n"
		<<"find a way to escape!\n"
		<<"\nTo leave current room all monsters inside must be defeated first.\n";


    std::cin.get();
}

bool checkWin(Hero hero, int lvlNumber, vector<Items> itemsBase)
{
	bool haveGoal = 0;
	if(lvlNumber == 1)
	{
		for(unsigned int i=0; i<hero.mInventory.size(); i++)
		{
			if(hero.mInventory[i] == itemsBase[itemsBase.size()-1].mID)
			{
				haveGoal = 1;
				break;
			}
		}

		if(haveGoal)
		{
			return 1;
		}
	}

	return 0;
}

void heroDmgDefSimulator()
{
	int dmg;
	int def;

    int itemsATT = 0;
    int combatItemFF = 0;

    int itemsDEF = 0;
    int defensiveItemFF = 0;

    int minDMG, maxDMG;
    int minDEF, maxDEF;
    for(int j=1; j<=50; j++) // j = level
    {
        minDMG = 5000;
        maxDMG = 0;
        minDEF = 5000;
        maxDEF = 0;
    	for(int i=1; i<=500; i++)
    	{
    		dmg = j + diceRoller(0.5*j+combatItemFF+1) + itemsATT;
            if(dmg>maxDMG) maxDMG = dmg;
            if(dmg<minDMG) minDMG = dmg;

    		def = 2*j + diceRoller(j+defensiveItemFF) + itemsDEF;
            if(def>maxDEF) maxDEF = def;
            if(def<minDEF) minDEF = def;
        }
    	cout<<j<<". DMG: "<<minDMG<<" - "<<maxDMG
    		<<", DEF: "<<minDEF<<" - "<<maxDEF<<endl;
    }
    std::cin.get();
    stop(0);
}

void displayExpTable()
{
	std::system("clear");

	int total_exp = 0;

	cout<<"EXPERIENCE TABLE\n";
	cout<<"To reach X level You need Y exp points at total,\n";
	cout<<"to jump from prev lvl to X lvl You must obtain Z points.\n";

	setCursor(0, 3);
	cout<<"X";
	setCursor(12, 3);
	cout<<"Y";
	setCursor(24, 3);
	cout<<"Z\n";
	for(int i=1; i<=50; i++)
	{
		total_exp += 20*pow((i - 1), 1.5);

		setCursor(0, 4+i);
		cout<<i;

		setCursor(12, 4+i);
		cout<<total_exp;

		setCursor(24, 4+i);
		cout<<(int)(20*pow((i - 1), 1.5));
	}

    std::cin.get();
}

void gameMenu()
{
    std::system("clear");
	setCursor(31, 6);
    std::cout<<"The Key of Gaerth!";
	setCursor(31, 12);
    std::cout<<"Press any key ...";

    getch();
}

char getch() 
{
    /*char buf = 0;
    struct termios old = {0};
    if(tcgetattr(0, &old) < 0)
    {
        perror("tcsetattr()");
    }

    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

    if(tcsetattr(0, TCSANOW, &old) < 0)
    {
        perror("tcsetattr ICANON");
    }

    if(read(0, &buf, 1) < 0)
    {
        perror ("read()");
    }
    
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if(tcsetattr(0, TCSADRAIN, &old) < 0)
    {
        perror ("tcsetattr ~ICANON");
    }

    return(buf);*/

    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

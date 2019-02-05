#include "datastruct.h"
#include "data.h"
#include "functions.h"

// ----------   LEVELS STACK    ----------
LevelsStack::LevelsStack(int a, vector<Items> itemsBase, vector<Monsters> monstersBase)
{  
    mnLevel = a;
    this->computeNRooms(mnLevel, 30);

    mRoomcontent = new RoomContent[mnRooms];
    // Setting mSelectedContent to 1
    for(int i=0; i<mnRooms; i++)
    {
        mRoomcontent[i].mSelectedContent = 0;
    }


    this->generateRoomsContent(1, itemsBase, monstersBase);

    pNext = NULL;
    pPrev = NULL;

    this->generateMap(MAP_SIZE);
}
void LevelsStack::computeNRooms(int nLevel, int max)
{
    int a = rand() % 3 + 2 + 1.1 * nLevel;

    if(a>=max) mnRooms = max;
    else mnRooms = a;
}
void LevelsStack::generateMap(int mapSize)
{
    int a;
    //----- MAP GENERATION -----
        //      ----- CLEARING -----
        for(int i=0; i<mapSize; i++)
        {
            for(int j=0; j<mapSize; j++)
            {
                mArraymap[i][j] = NOTHING;
                mSeenmap[i][j] = 0; // ------ HERE!!!! ----- 
            }
        }
        //      ----- FIRST ROOM IN CENTER -----
        mArraymap[mapSize/2][mapSize/2] = NORMAL;

        //      ----- GENERATION ITSELF -----
        a = 1; // counter for nu of rooms 
        int x, y;
        while(a<mnRooms)
        {
            x = rand()%mapSize;
            y = rand()%mapSize;

            if(mArraymap[y][x]==NOTHING)
            {
                if(y>0 && mArraymap[y-1][x]==NORMAL)
                {
                    mArraymap[y][x] = NORMAL;
                    a++;
                }
                else if(y<mapSize-1 && mArraymap[y+1][x]==NORMAL)
                {
                    mArraymap[y][x] = NORMAL;
                    a++;
                }
                else if(x>0 && mArraymap[y][x-1]==NORMAL)
                {
                    mArraymap[y][x] = NORMAL;
                    a++;
                }
                else if(x<mapSize-1 && mArraymap[y][x+1]==NORMAL)
                {
                    mArraymap[y][x] = NORMAL;
                    a++;
                }
            }
        }
        //      ----- ROOM TYPE -----
        int counter;
        //              ----- STAIRS -----

        a = rand()%mnRooms + 1;
        counter = 0;

        for(int i=0; i<mapSize; i++)
        {
            for(int j=0; j<mapSize; j++)
            {
                if(mArraymap[i][j]==NORMAL) counter++;
                if(counter==a)
                {
                    mArraymap[i][j]=DOWNSTAIRS;
                    i=mapSize;
                    j=mapSize;
                }
            }
        }
        if(mnLevel!=1)
        {
            a = rand()%(mnRooms - 1) + 1;
            counter = 0;

            for(int i=0; i<mapSize; i++)
            {
                for(int j=0; j<mapSize; j++)
                {
                    if(mArraymap[i][j]==NORMAL) counter++;
                    if(counter==a)
                    {
                        mArraymap[i][j]=UPSTAIRS;
                        mSeenmap[i][j]=1;
                        i=mapSize;
                        j=mapSize;
                    }
                }
            }
            //              ----- FINISH -----
            if(mnLevel==10)
            {
                a = rand()%(mnRooms - 2) + 1;
                counter = 0;

                for(int i=0; i<mapSize; i++)
                {
                    for(int j=0; j<mapSize; j++)
                    {
                        if(mArraymap[i][j]==NORMAL) counter++;
                        if(counter==a)
                        {
                            mArraymap[i][j]=FINISH;
                            i=mapSize;
                            j=mapSize;
                        }
                    }
                }
            }
        }
        //              ----- START -----
        else if(mnLevel==1)
        {
            a = rand()%(mnRooms - 1) + 1;
            counter = 0;

            for(int i=0; i<mapSize; i++)
            {
                for(int j=0; j<mapSize; j++)
                {
                    if(mArraymap[i][j]==NORMAL) counter++;
                    if(counter==a)
                    {
                        mArraymap[i][j]=START;
                        mSeenmap[i][j]=1;
                        i=mapSize;
                        j=mapSize;
                    }
                }
            }
        }

        //              ----- HIDDEN -----
/*        if(rand()%100+1<=90) // 90% for hidden room
        {
            int success=0;
            while(success==0)
            {
                x = rand()%mapSize;
                y = rand()%mapSize;

                if(mArraymap[y][x]==NOTHING)
                {
                    if(y>0 && mArraymap[y-1][x]!=NOTHING)
                    {
                        success=1;
                    }
                    else if(y<mapSize-1 && mArraymap[y+1][x]!=NOTHING)
                    {
                        success=1;
                    }
                    else if(x>0 && mArraymap[y][x-1]!=NOTHING)
                    {
                        success=1;
                    }
                    else if(x<mapSize-1 && mArraymap[y][x+1]!=NOTHING)
                    {
                        success=1;
                    }
                }
            }
            mArraymap[y][x]=HIDDEN;
            //mnRooms++;
        }*/
}
void LevelsStack::generateRoomsContent(bool generateItems, vector<Items> itemsBase, vector<Monsters> monstersBase)
{
    vector<int> randomizedItems; // arr of items IDs
    vector<int> randomizedMonsters; // arr of monster IDs

    //----- GENERATING ROOM CONTENT -----
    if(generateItems)
    {
        for(unsigned int i=0; i<itemsBase.size(); i++)
        {
            if(itemsBase[i].mRespfrom<=mnLevel && mnLevel<=itemsBase[i].mRespfrom + itemsBase[i].mResplen - 1)
            {
                if(rand()%100+1<=itemsBase[i].mRarity) // checking if item generate
                {
                    randomizedItems.push_back(itemsBase[i].mID);
                }
            }
        }
        if(mnLevel==GOAL_LEVEL) // ---- GOAL LEVEL ----
        {
            randomizedItems.push_back(itemsBase[itemsBase.size()-1].mID);
        }
    }
    else if(generateItems==0)
    {
        for(int i=0; i<mnRooms; i++)
        {
            mRoomcontent[i].mMonsters.clear();
        }
    }

    for(unsigned int i=0; i<monstersBase.size(); i++)
    {
        if(monstersBase[i].mRespfrom<=mnLevel && mnLevel<=monstersBase[i].mRespfrom + monstersBase[i].mResplen - 1)
        {
            if(rand()%100+1<=monstersBase[i].mRarity) // checking if item generate
            {
                randomizedMonsters.push_back(monstersBase[i].mID);
            }
        }
    }

    //----- ASSIGNING ROOM CONTENT -----
    //      ----- Items -----
    for(unsigned int i=0; i<randomizedItems.size(); i++)
    {
        mRoomcontent[rand()%mnRooms].mItems.push_back(randomizedItems[i]);
    }
    //      ----- Monsters -----
    for(unsigned int i=0; i<randomizedMonsters.size(); i++)
    {
        mRoomcontent[rand()%mnRooms].mMonsters.push_back(randomizedMonsters[i]);
    }
}
void LevelsStack::displayRoomContent(int roomNumber, int heroCoorX, int heroCoorY, vector<Items> itemsBase, vector<Monsters> monstersBase)
{
    short int startingPointX = 1;
    short int startingPointY = 1;

    if(mArraymap[heroCoorY][heroCoorX]!=HIDDEN)
    {
        // Cursor
        if(mRoomcontent[roomNumber-1].mSelectedContent > 0 && 
            mRoomcontent[roomNumber-1].mSelectedContent <=
                mRoomcontent[roomNumber-1].mMonsters.size() + mRoomcontent[roomNumber-1].mItems.size())
        {
            if(mRoomcontent[roomNumber-1].mSelectedContent<=mRoomcontent[roomNumber-1].mMonsters.size())
            {
                setCursor(startingPointX, startingPointY+mRoomcontent[roomNumber-1].mSelectedContent);
            }
            else
            {
                setCursor(startingPointX, startingPointY+mRoomcontent[roomNumber-1].mSelectedContent+1);
            }
                cout<<">";  
        }

        setCursor(startingPointX+2, startingPointY);

        drawLabel("Monsters");
        
        for(unsigned int i=0; i<mRoomcontent[roomNumber-1].mMonsters.size(); i++)
        {
            setCursor(startingPointX+2, startingPointY+i+1);
            cout<<monstersBase[(mRoomcontent[roomNumber-1].mMonsters[i])-1].mName;
        }

        startingPointY += mRoomcontent[roomNumber-1].mMonsters.size() + 1;
        setCursor(startingPointX+2, startingPointY);

        drawLabel(" Items  ");

        for(unsigned int i=0; i<mRoomcontent[roomNumber-1].mItems.size(); i++)
        {
            setCursor(startingPointX+2, startingPointY+i+1);
            cout<<itemsBase[(mRoomcontent[roomNumber-1].mItems[i])-1].mName;
        }
    }

    startingPointX = 26;
    startingPointY = 17;

    setCursor(startingPointX, startingPointY);
    cout<<"Dung. lv: "<<mnLevel;
    setCursor(startingPointX, startingPointY+1);
    cout<<"Room type:";
    setCursor(startingPointX, startingPointY+2);
    
    if(mArraymap[heroCoorY][heroCoorX] == NOTHING) cout<<"NOTHING";
    else if(mArraymap[heroCoorY][heroCoorX] == NORMAL) cout<<"NORMAL";
    else if(mArraymap[heroCoorY][heroCoorX] == START) cout<<"START";
    else if(mArraymap[heroCoorY][heroCoorX] == FINISH) cout<<"FINISH";
    else if(mArraymap[heroCoorY][heroCoorX] == UPSTAIRS) cout<<"UPSTAIRS";
    else if(mArraymap[heroCoorY][heroCoorX] == DOWNSTAIRS) cout<<"DOWNSTAIRS";
    else if(mArraymap[heroCoorY][heroCoorX] == HIDDEN) cout<<"HIDDEN";
}
int LevelsStack::computeRoomNumber(int heroCoorX, int heroCoorY)
{
    int roomNumber=0;
    for(int i=0; i<MAP_SIZE; i++)
    {
        for(int j=0; j<MAP_SIZE; j++)
        {
            if(mArraymap[i][j]!=NOTHING && mArraymap[i][j]!=HIDDEN)
            {
                roomNumber++;
            }
            if(i==heroCoorY && j==heroCoorX)
            {
                i = MAP_SIZE;
                j = MAP_SIZE;
            }
        }
    }
    return roomNumber;
}
void pushLevelsStack(LevelsStack** head, vector<Items> itemsBase, vector<Monsters> monstersBase)
{
    LevelsStack* new_head = NULL;

    if(*head == NULL)
    {
        new_head = new LevelsStack(1, itemsBase, monstersBase);
        *head = new_head;
    }
    else
    {
        new_head = new LevelsStack((*head)->mnLevel+1, itemsBase, monstersBase);
        new_head->pPrev = *head;
        (*head)->pNext = new_head;
        *head = new_head;
    }
}

// ----------   HERO    ----------
Hero::Hero(string mName)
{
    this->mName = mName;
    mEXP = 0;
    mEXP4nextLVL = 0;
    mLVL = 1;
    mHP = 10;
    
    mCoorx = 0;
    mCoory = 0;

    mMaxInvSize = 10;

    this->setStartingINV();

    mSelectedItem = 0;
}
void Hero::setInitCoor(RoomType arrayMap[][MAP_SIZE], bool transistionType)
{
    for(int i=0; i<MAP_SIZE; i++) // y
    {
        for(int j=0; j<MAP_SIZE; j++) // x
        {
            if(transistionType==0)
            {
                if(arrayMap[i][j]==UPSTAIRS || arrayMap[i][j]==START)
                {
                    mCoorx = j;
                    mCoory = i;

                    i = MAP_SIZE;
                    j = i;
                }
            }
            else if(arrayMap[i][j]==DOWNSTAIRS)
            {
                mCoorx = j;
                mCoory = i;

                i = MAP_SIZE;
                j = i;
            }
        }
    }
}
void Hero::setStartingINV()
{
    for(int i=1; i<=2; i++)
    {
        mInventory.push_back(i);
    }
}
void Hero::displayHeroItems(vector<Items> itemsBase)
{
    short int startingPointX = 42;
    short int startingPointY = 1;

    // Cursor
    if(mSelectedItem > 0 && mSelectedItem <= mEQ.size() + mInventory.size())
    {
        if(mSelectedItem <= mEQ.size())
        {
            setCursor(startingPointX, startingPointY+mSelectedItem);
        }
        else
        {
            setCursor(startingPointX, startingPointY+mSelectedItem+1);
        }
        cout<<">";
    }

    setCursor(startingPointX+2, startingPointY);
    drawLabel("Equipment");

    for(unsigned int i=0; i<mEQ.size(); i++)
    {
        setCursor(startingPointX+2, startingPointY+i+1);
        cout<<itemsBase[mEQ[i]-1].mName;
    }

    startingPointY += mEQ.size() + 1;
    setCursor(startingPointX+2, startingPointY);
    drawLabel("Inventory");

    for(unsigned int i=0; i<mInventory.size(); i++)
    {
        setCursor(startingPointX+2, startingPointY+i+1);
        cout<<itemsBase[mInventory[i]-1].mName;
    }
}
void Hero::displayStats(vector<Items> itemsBase)
{
    this->mSetStringAttDef(itemsBase);

    short int startingPointX = 68;
    short int startingPointY = 1;

    setCursor(startingPointX, startingPointY);
    cout<<"-"<<"-"<<" Hero "<<"-"<<"-";

    setCursor(startingPointX, startingPointY+2);
    cout<<"LVL: "<<mLVL;

    setCursor(startingPointX, startingPointY+3);
    cout<<"HP: "<<mHP;
    setCursor(startingPointX, startingPointY+4);
    cout<<"maxHP: "<<mLVL * 10;

    setCursor(startingPointX, startingPointY+7);
    cout<<"EXP: ";
    setCursor(startingPointX, startingPointY+8);
    cout<<mEXP;
    setCursor(startingPointX, startingPointY+9);
    cout<<"Next LVL: ";
    setCursor(startingPointX, startingPointY+10);
    cout<<mEXP4nextLVL;

    setCursor(startingPointX, startingPointY+13);
    cout<<"DMG: ";
    setCursor(startingPointX, startingPointY+14);
    cout<<mDMG;
    setCursor(startingPointX, startingPointY+15);
    cout<<"DEF: ";
    setCursor(startingPointX, startingPointY+16);
    cout<<mDEF;
}
void Hero::mSetStringAttDef(vector<Items> itemsBase)
{
    int nDicesATT = mLVL * 0.5 + 1;
    int nDicesDEF = mLVL * 0.5 + 1;

    int itemsATT = mLVL;
    int itemsDEF = mLVL;

    string tmp;

    for(unsigned int i=0; i<mEQ.size(); i++)
    {
        itemsATT += itemsBase[mEQ[i]-1].mAttack;
        itemsDEF += itemsBase[mEQ[i]-1].mDefense;

        if(itemsBase[mEQ[i]-1].mItemtype==COMBAT)
        {
            nDicesATT += itemsBase[mEQ[i]-1].mFortuityfactor;
        }
        else if(isItDefensive(itemsBase[mEQ[i]-1].mItemtype))
        {
            nDicesDEF += itemsBase[mEQ[i]-1].mFortuityfactor;
        }
    }

    sprintf((char*)tmp.c_str(), "%d", nDicesATT);
    mDMG = tmp.c_str();
    mDMG.append("D3+");
    sprintf((char*)tmp.c_str(), "%d", itemsATT);
    mDMG.append(tmp.c_str());

    sprintf((char*)tmp.c_str(), "%d", nDicesDEF);
    mDEF = tmp.c_str();
    mDEF.append("D3+");
    sprintf((char*)tmp.c_str(), "%d", itemsDEF);
    mDEF.append(tmp.c_str());
}
bool Hero::fight(LevelsStack* levelsStack, vector<Items> itemsBase, vector<Monsters> monstersBase)
{
    int roomNumber =
        levelsStack->computeRoomNumber(mCoorx, mCoory)-1;
    unsigned int selectedContent = levelsStack->mRoomcontent[roomNumber].mSelectedContent;

    if(selectedContent >=1 && selectedContent <= levelsStack->mRoomcontent[roomNumber].mMonsters.size())
    {
        int monsterIndex =
            levelsStack->mRoomcontent[roomNumber].mMonsters[selectedContent-1]-1;
        //monstersBase[monsterIndex];
        bool didYouDie = 0;
        bool endOfFight = 0;
        bool skipFight = 0;
        bool whoseTurn;
        if(rand()%5 < 3) whoseTurn = 1; // 3/5 chance for start a fight
        else whoseTurn = 0;

        int monLVL = monstersBase[monsterIndex].mLevel;
        int monBaseDMG = monstersBase[monsterIndex].mAttack;
        int monBaseDEF = monstersBase[monsterIndex].mDefense;
        int monHP = monstersBase[monsterIndex].mHP;

        int hDMG = mLVL;
        int hDEF = mLVL;
        int dicesForHeroDMG = 0.5*mLVL + 1;
        int dicesForHeroDEF = 0.5*mLVL + 1;

        signed int calculatedDMG;
        int calculatedATT;
        int calculatedDEF;

        ostringstream oss;
        vector<string> info;

        char input;

        for(unsigned int i=0; i<mEQ.size(); i++)
        {
            hDMG += itemsBase[mEQ[i]-1].mAttack;
            hDEF += itemsBase[mEQ[i]-1].mDefense;

            if(itemsBase[mEQ[i]-1].mItemtype==COMBAT)
            {
                dicesForHeroDMG += itemsBase[mEQ[i]-1].mFortuityfactor;
            }
            else if(isItDefensive(itemsBase[mEQ[i]-1].mItemtype))
            {
                dicesForHeroDEF += itemsBase[mEQ[i]-1].mFortuityfactor;
            }
        }

        /*levelsStack->mRoomcontent[roomNumber].mMonsters.erase(
            levelsStack->mRoomcontent[roomNumber].mMonsters.begin() + selectedContent-1);*/

        while(!endOfFight)
        {
            calculatedDMG = 0;
            oss.str("");
            oss.clear();

            if(monHP <= 0)
            {
                levelsStack->mRoomcontent[roomNumber].mMonsters.erase(
                    levelsStack->mRoomcontent[roomNumber].mMonsters.begin() + selectedContent-1);

                // this -> mEXP += monstersBase[monsterIndex].mEXP;
                expManagement(monstersBase[monsterIndex].mEXP);

                oss<<"You defeated "<<monstersBase[monsterIndex].mName
                    <<" gaining "<<monstersBase[monsterIndex].mEXP<<" EXP points.";

                info.push_back(oss.str());

                if(levelsStack->mRoomcontent[roomNumber].mSelectedContent >= 
                    levelsStack->mRoomcontent[roomNumber].mMonsters.size() + 
                    levelsStack->mRoomcontent[roomNumber].mItems.size())
                {
                    levelsStack->mRoomcontent[roomNumber].mSelectedContent = 
                    levelsStack->mRoomcontent[roomNumber].mMonsters.size() + 
                    levelsStack->mRoomcontent[roomNumber].mItems.size();
                }

                endOfFight = 1;
                didYouDie = 0;
            }
            else if(mHP <= 0)
            {
                oss<<"You are defeated by "<<monstersBase[monsterIndex].mName
                    <<".";

                info.push_back(oss.str());

                endOfFight = 1;
                didYouDie = 1;
            }
            else if(whoseTurn) // player attack
            {
                calculatedATT = (hDMG + diceRoller(dicesForHeroDMG));
                calculatedDEF = (monLVL + diceRoller(monBaseDEF));
                calculatedDMG = calculatedATT - calculatedDEF;

                if(calculatedDMG > 0)
                {
                    monHP -= calculatedDMG;
                   
                    oss<<"A "<<monstersBase[monsterIndex].mName
                        <<" loses "<<calculatedDMG<<" (="
                        <<calculatedATT<<"-"<<calculatedDEF
                        <<") HP (left: "<<monHP<<") due to your attack.";

                    info.push_back(oss.str());
                }
                else
                {
                    oss<<"A "<<monstersBase[monsterIndex].mName
                        <<" fully defended your attack ("
                        <<calculatedATT<<"-"<<calculatedDEF
                        <<"="<<calculatedDMG<<").";

                    info.push_back(oss.str());
                }

                whoseTurn = 0;
            }
            else if(whoseTurn==0) // monster attack
            {
                calculatedATT = (monLVL + diceRoller(monBaseDMG));
                calculatedDEF = (hDEF + diceRoller(dicesForHeroDEF));
                calculatedDMG = calculatedATT - calculatedDEF;

                if(calculatedDMG > 0) 
                {
                    mHP -= calculatedDMG;

                    oss<<"You lose "<<calculatedDMG<<" (="
                        <<calculatedATT<<"-"<<calculatedDEF
                        <<") HP due to attack by a "
                        <<monstersBase[monsterIndex].mName<<".";

                    info.push_back(oss.str());

                    setCursor(72, 4);
                    cout<<"       ";

                    displayStats(itemsBase);
                }
                else
                {
                    oss<<"You fully defended "<<monstersBase[monsterIndex].mName
                        <<"'s attack ("<<calculatedATT<<"-"<<calculatedDEF
                        <<"="<<calculatedDMG<<").";
                        
                    info.push_back(oss.str());
                }

                whoseTurn = 1;
            }

            displayInfoBox(info);

            if(skipFight==0)
            {
                input = getch();
                if(input == (char)27)
                {
                    info.push_back("Exit for sure? (y / anything else)");
                    displayInfoBox(info);

                    input = getch();
                    if(input == 'y' || input == 'Y')
                    {
                        return 1;
                    }
                }
                else if(input == 's')
                {
                    skipFight = 1;
                }         
            }
            else
            {
                usleep(20);
                //Sleep(20);
            }
        }

        if(didYouDie==0) return 0;
        else return 1;

    }
    return 0;
}
void Hero::expManagement(int expToAdd)
{
    bool finish = 0;
    int expNeeded;
    mEXP += expToAdd;

    while(finish==0)
    {    
        expNeeded = 0;
        for(int i=1; i<=mLVL+1; i++)
        {
            expNeeded += 20*pow((i - 1), 1.5);
        }

        if(mEXP >= expNeeded)
        {
            mLVL++;
            addHP((10*mLVL*1)/4); // 25% of max HP
        }
        else
        {
            finish = 1;
        }
    }

    expNeeded = 0;
    for(int i=1; i<=mLVL+1; i++)
    {
        expNeeded += 20*pow((i - 1), 1.5);
    }

    mEXP4nextLVL = expNeeded - mEXP;

}
void Hero::addHP(int hpToAdd)
{
    if(hpToAdd+mHP >= mLVL*10)
    {
        mHP = mLVL*10;
    }
    else
    {
        mHP += hpToAdd;
    }
}
// ----------   ITEMS    ----------
Items::Items(short int ID, int fortuity, int att, int def, int hpCure, int respFrom, int respLen, int rarity, ItemType itemType, string name)
{
    mID = ID;

    mFortuityfactor = fortuity;
    mAttack = att;
    mDefense = def;
    mHPcure = hpCure;

    mRespfrom = respFrom;
    mResplen = respLen;
    mRarity = rarity;
    
    mItemtype = itemType;
    mName = name;
}

// ----------   MONSTERS    ----------
Monsters::Monsters(short int ID, int lvl, int att, int def, int hp, int exp, int respFrom, int respLen, int rarity, string name)
{
    mID = ID;

    mLevel = lvl;
    mAttack = att;
    mDefense = def;
    mHP = hp;
    mEXP = exp;

    mRespfrom = respFrom;
    mResplen = respLen;
    mRarity = rarity;

    mName = name;
}

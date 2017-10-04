#include "StudentWorld.h"
#include "Actor.h"
#include "Compiler.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

int StudentWorld::returnWinningAntNumber(int antOne, int antTwo, int antThree, int antFour) const
{
    int arr[4] = {antOne, antTwo, antThree, antFour};
    int biggest = -1;
    int biggestInt = 5;
    for (int k = 0; k < 4; k++)
    {
        if (arr[k] > biggestInt)
            biggest = k;
        else if (biggest != -1 && arr[k] == arr[biggest])
        {
            if (timeOfIncrement[k] < timeOfIncrement[biggest])
                biggest = k;
        }
    }
    
    return biggest;
}

Actor* StudentWorld::getEdibleAt(int x, int y)
{
    for (list<Actor*>::iterator it = actorList[x][y].begin(); it != actorList[x][y].end(); it++)
    {
        if ((*it)->isEdible())
        {
            return (*it);
        }
    }
    
    return nullptr;

}

bool StudentWorld::isEnemyAt(int x, int y, int colony) const
{
    for (list<Actor*>::const_iterator it = actorList[x][y].begin(); it != actorList[x][y].end(); it++)
    {
        if ((*it)->isEnemy(colony))
            return true;
    }
    
    return false;
    
}

void StudentWorld::addActor(Actor* actor)
{
    actorList[actor->getX()][actor->getY()].push_back(actor);
}

bool StudentWorld::stunAllStunnableAt(int x, int y)
{
    bool returnVal = false;
    for (list<Actor*>::iterator it = actorList[x][y].begin(); it != actorList[x][y].end(); it++)
    {
        (*it)->getStunned();
        returnVal = true;
    }
    
    return returnVal;
}

bool StudentWorld::poisonAllPoisonableAt(int x, int y)
{
    bool returnVal = false;
    for (list<Actor*>::iterator it = actorList[x][y].begin(); it != actorList[x][y].end(); it++)
    {
        (*it)->getPoisoned();
        returnVal = true;
    }
    
    return returnVal;

}

bool StudentWorld::biteEnemyAt(Actor* me, int colony, int biteDamage)
{
    
    vector<Actor*> biteableActors;
    for (list<Actor*>::iterator it = actorList[me->getX()][me->getY()].begin(); it != actorList[me->getX()][me->getY()].end(); it++)
    {
        if ((*it)->isEnemy(colony) && (*it) != me)
        {
            biteableActors.push_back(*it);
        }
    }
    
    if (biteableActors.size() != 0)
    {
        int k = randInt(0, biteableActors.size() - 1);
        biteableActors[k]->getBitten(biteDamage);
        return true;
    }
    
    return false;
    
    
}

bool StudentWorld::canMoveTo(int x, int y) const
{
    for (list<Actor*>::const_iterator it = actorList[x][y].begin(); it != actorList[x][y].end(); it++)
    {
        if ((*it)->blocksMovement())
        {
            return false;
        }
    }
    
    return true;
}


bool StudentWorld::isDangerAt(int x, int y, int colony) const
{
    for (list<Actor*>::const_iterator it = actorList[x][y].begin(); it != actorList[x][y].end(); it++)
    {
        if ((*it)->isDangerous(colony))
            return true;
    }
    
    return false;
}

Actor* StudentWorld::getPheromoneAt(int x, int y, int colony)
{
    for (list<Actor*>::iterator it = actorList[x][y].begin(); it != actorList[x][y].end(); it++)
    {
        if ((*it)->isPheromone(colony))
        {
            return *it;
        }
    }
    
    return nullptr;
}

bool StudentWorld::isAnthillAt(int x, int y, int colony) const
{
    for (list<Actor*>::const_iterator it = actorList[x][y].begin(); it != actorList[x][y].end(); it++)
    {
        if ((*it)->isMyAnthill(colony))
        {
            return true;
        }
    }
    return false;
}

void StudentWorld::removeDeadActors()
{
    for (int k = 0; k < 64; k++)
    {
        for (int w = 0; w < 64; w++)
        {
            for (list<Actor*>::iterator it = actorList[w][k].begin(); it != actorList[w][k].end();)
            {
                if (!(*it)->isLiving())
                {
                    (*it)->setVisible(false);
                    delete (*it);
                    it = actorList[w][k].erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
    }
}

void StudentWorld::increaseScore(int antID)
{
    if (antID == 0)
    {
        timeOfIncrement[0] = ticks;
        numAntsZero++;
    }
    else if (antID == 1)
    {
        timeOfIncrement[1] = ticks;
        numAntsOne++;
    }
    else if (antID == 2)
    {
        timeOfIncrement[2] = ticks;
        numAntsTwo++;
    }
    else if (antID == 3)
    {
        timeOfIncrement[3] = ticks;
        numAntsThree++;
    }
}

bool StudentWorld::loadFile()
{
    string fieldFileName;
    Field f;
    std::string fieldFile = getFieldFilename();
    
    string error;
    if (f.loadField(fieldFile, error) != Field::LoadResult::load_success)
    {
        setError(fieldFile + " " + error);
        return false;
    }
    
    
    Compiler *compilerForEntrant0, *compilerForEntrant1,
    *compilerForEntrant2, *compilerForEntrant3;
    
    vector<string> fileNames = getFilenamesOfAntPrograms();
    compilerForEntrant0 = new Compiler;
    string errorCompiler;

    
    if ( ! compilerForEntrant0->compile(fileNames[0], errorCompiler) )
    {
        setError(fileNames[0] + " " + error);
        return false;
    }
    
    nameZero = compilerForEntrant0->getColonyName();
    compilerList[0] = compilerForEntrant0;
    numCompilers++;
    
    if (fileNames.size() >= 2)
    {
        compilerForEntrant1 = new Compiler;
        if ( ! compilerForEntrant1->compile(fileNames[1], errorCompiler) )
        {
            setError(fileNames[1] + " " + error);
            return false;
        }
        nameOne = compilerForEntrant1->getColonyName();
        compilerList[1] = compilerForEntrant1;
        numCompilers++;
    }
    
    if (fileNames.size() >= 3)
    {
        compilerForEntrant2 = new Compiler;
        if ( ! compilerForEntrant2->compile(fileNames[2], errorCompiler) )
        {
            setError(fileNames[2] + " " + error);
            return false;
        }
        nameTwo = compilerForEntrant2->getColonyName();
        compilerList[2] = compilerForEntrant2;
        numCompilers++;
    }

    if (fileNames.size() == 4)
    {
        compilerForEntrant3 = new Compiler;
        if ( ! compilerForEntrant3->compile(fileNames[3], errorCompiler) )
        {
            setError(fileNames[3] + " " + error);
            return false;
        }
        nameThree = compilerForEntrant3->getColonyName();
        compilerList[3] = compilerForEntrant3;
        numCompilers++;
    }

    for (int k = 0; k < 64; k++)
    {
        for (int w = 0; w < 64; w++)
        {
            Field::FieldItem item = f.getContentsOf(w,k);
            if (item == Field::FieldItem::rock)
                actorList[w][k].push_back(new Pebble(w, k, this));
            if (item == Field::FieldItem::grasshopper)
                actorList[w][k].push_back(new babyGrasshopper(w, k, this));
            if (item == Field::FieldItem::food)
                actorList[w][k].push_back(new Food (w, k, 6000, this));
            if (item == Field::FieldItem::poison)
                actorList[w][k].push_front(new Poison (w, k, this));
            if (item == Field::FieldItem::water)
                actorList[w][k].push_front(new Water (w, k, this));
            if (item == Field::FieldItem::anthill0)
                actorList[w][k].push_back(new Anthill (w, k, 0, this, compilerForEntrant0));
            if (fileNames.size() >= 2)
            {
                if (item == Field::FieldItem::anthill1)
                    actorList[w][k].push_back(new Anthill (w, k, 1, this, compilerForEntrant1));
            }
            if (fileNames.size() >= 3)
            {
                if (item == Field::FieldItem::anthill2)
                    actorList[w][k].push_back(new Anthill (w, k, 2, this, compilerForEntrant2));
            }
            if (fileNames.size() == 4)
            {
                if (item == Field::FieldItem::anthill3)
                    actorList[w][k].push_back(new Anthill (w, k, 3, this, compilerForEntrant3));
            } 
        }
    }
    
    return true;
}

int StudentWorld::init()
{
    ticks = 0;
    numCompilers = 0;
    numAntsZero = numAntsTwo = numAntsThree = numAntsOne = 0;
    nameZero = nameOne = nameTwo = nameThree = "";
    for (int k = 0; k < 4; k++)
    {
        timeOfIncrement[k] = 5000;
    }
    
    if (!loadFile())
        return GWSTATUS_LEVEL_ERROR;
    else
        return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    ticks++;
    
    for (int k = 0; k < 64; k++)
    {
        for (int w = 0; w < 64; w++)
        {
            for (list<Actor*>::iterator it = actorList[w][k].begin(); it != actorList[w][k].end(); it++)
            {
                (*it)->resetMoved();
            }
        }
    }
    
    for (int k = 0; k < 64; k++)
    {
        for (int w = 0; w < 64; w++)
        {
            for (list<Actor*>::iterator it = actorList[w][k].begin(); it != actorList[w][k].end();)
            {
                if ((*it)->hasNotMovedYet())
                {
                    if ((*it)->isLiving())
                    {
                        Actor* ptr = *it;
                        int oldX = (*it)->getX();
                        int oldY = (*it)->getY();
                        (*it)->doSomething();
                        (*it)->Moved();
                        
                        if (oldX != (*it)->getX() || oldY != (*it)->getY())
                        {
                            actorList[(*it)->getX()][(*it)->getY()].push_back(ptr);
                            it = actorList[w][k].erase(it);
                            continue;
                        }
                    }
                }
                it++;
            }
        }
    }
    
    removeDeadActors();
    
    setDisplayText();
    
    if (ticks == 2000)
    {
        int winner = returnWinningAntNumber(numAntsZero, numAntsOne, numAntsTwo, numAntsThree);
        int arr[4] = {numAntsZero, numAntsOne, numAntsTwo, numAntsThree};
        if (arr[winner] >= 6)
        {
            if (winner == 0)
            {
                setWinner(nameZero);
            }
            if (winner == 1)
            {
                setWinner(nameOne);
            }
            if (winner == 2)
            {
                setWinner(nameTwo);
            }
            if (winner == 3)
            {
                setWinner(nameThree);
            }
            return GWSTATUS_PLAYER_WON;
        }
        else
            return GWSTATUS_NO_WINNER;
    }

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::setDisplayText()
{
    int currentTicks = getTicks();
    int ants0 = numAntsZero;
    int ants1 = numAntsOne;
    int ants2 = numAntsTwo;
    int ants3 = numAntsThree;
    int winningAntNumber = returnWinningAntNumber(ants0, ants1, ants2, ants3);
    
    string s = stringFormatter(currentTicks, ants0, ants1, ants2, ants3, winningAntNumber);
    
    setGameStatText(s);
    
}

string StudentWorld::stringFormatter(int ticks, int ants0, int ants1, int ants2, int ants3, int winningAntNumber)
{
    ostringstream oss;
    oss << "Ticks:" << setw(5) << (2000-ticks) << " - ";
    
    vector<string> fileNames = getFilenamesOfAntPrograms();

    if (numCompilers >= 1)
    {
        oss << nameZero;
        if (winningAntNumber == 0)
        {
            oss << '*';
        }
        oss << ":" << oss.fill('0') << setw(2) << ants0 << " ants  ";
    }
    if (numCompilers >= 2)
    {
        oss.fill(' ');
        oss << nameTwo;
        if (winningAntNumber == 1)
        {
            oss << '*';
        }
        oss << ":" << oss.fill('0') << setw(2) << ants1 << " ants  ";
    }
    if (numCompilers >= 3)
    {
        oss.fill(' ');
        oss << nameTwo;
        if (winningAntNumber == 2)
        {
            oss << '*';
        }
        oss << ":" << oss.fill('0') << setw(2) << ants2 << " ants  ";
    }
    if (numCompilers == 4)
    {
        oss.fill(' ');
        oss << nameThree;
        if (winningAntNumber == 3)
        {
            oss << '*';
        }
        oss << ":" << oss.fill('0') << setw(2) << ants3 << " ants";
    }

    return oss.str();
}


void StudentWorld::cleanUp()
{
    for (int k = 0; k < 64; k++)
        for (int w = 0; w < 64; w++)
        {
            for (list<Actor*>::iterator it = actorList[w][k].begin(); it != actorList[w][k].end();)
            {
                delete (*it);
                it = actorList[w][k].erase(it);
            }
        }
    
    for (int w = 0; w < numCompilers; w++)
        delete compilerList[w];
    
    numCompilers = 0;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

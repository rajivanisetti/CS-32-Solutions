#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Field.h"
#include <string>
#include <list>
using namespace std;

class Actor;
class Compiler;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
    {
    }
    
    virtual int init();
    
    virtual int move();
    
    void cleanUp();
    
    bool loadFile();
    
    Actor* getEdibleAt(int x, int y);
    
    void addActor(Actor* actor);
    
    int getTicks() const {return ticks;}
    
    int returnWinningAntNumber(int antOne, int antTwo, int antThree, int antFour) const;
    
    bool canMoveTo(int x, int y) const;
    
    bool stunAllStunnableAt(int x, int y);
    
    bool poisonAllPoisonableAt (int x, int y);
    
    bool biteEnemyAt(Actor* me, int colony, int biteDamage);
    
    void increaseScore(int antID);
    
    bool isEnemyAt(int x, int y, int colony) const;
    
    void setDisplayText();
    
    Actor* getPheromoneAt(int x, int y, int colony);
    
    string stringFormatter(int ticks, int ants0, int ants1, int ants2, int ants3, int winningAntNumber);
    void removeDeadActors();
    
    bool isAnthillAt(int x, int y, int colony) const;
    
    bool isDangerAt(int x, int y, int colony) const;
    
    ~StudentWorld();
    
private:
    list<Actor*> actorList[64][64];
    int ticks;
    int numAntsZero;
    int numAntsTwo;
    int numAntsThree;
    int numAntsOne;
    int timeOfIncrement[4];
    string nameOne;
    string nameTwo;
    string nameThree;
    string nameZero;
    Compiler* compilerList[4];
    int numCompilers;
    
    
};

#endif // STUDENTWORLD_H_

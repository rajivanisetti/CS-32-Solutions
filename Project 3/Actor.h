#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "Compiler.h"

class StudentWorld;
class Compiler;
GraphObject::Direction randomDirection();


class Actor: public GraphObject
{
public:
    Actor(StudentWorld* world, int imageID, int startX, int startY, int depth, Direction direction = none)
    :GraphObject(imageID, startX, startY, direction, depth), m_world(world), hasMoved(false)
    {
        setVisible(true);
    }
    
    virtual void doSomething() = 0;
    
    virtual void getStunned()
    {
        return;
    }
    
    virtual int returnHitPoints() const
    {
        return -1;
    }
    
    virtual void changeHealth(int amount)
    {
        return;
    }
    
    virtual void getPoisoned()
    {
        return;
    }
    
    virtual bool isEnemy(int colony) const
    {
        return false;
    }
    
    virtual bool blocksMovement() const
    {
        return false;
    }
    
    virtual void getBitten(int amount)
    {
        return;
    }
    
    virtual bool isDangerous(int colony) const
    {
        return false;
    }
    
    virtual bool isEdible() const
    {
        return false;
    }
    
    virtual bool isMyAnthill(int colony) const
    {
        return false;
    }
    
    virtual bool isPheromone(int colony) const
    {
        return false;
    }
    
    virtual ~Actor()
    {
        setVisible(false);
    }
    
    StudentWorld* returnWorld() const
    {
        return m_world;
    }
    
    virtual bool isLiving() const
    {
        return true;
    }
    
    void Moved()
    {
        hasMoved = true;
    }
    
    bool hasNotMovedYet() const
    {
        return !hasMoved;
    }
    
    void resetMoved()
    {
        hasMoved = false;
    }
    
    
private:
    bool hasMoved;
    StudentWorld* m_world;
};

class Pebble: public Actor
{
public:
    Pebble(int startX, int startY, StudentWorld* world)
    :Actor(world, IID_ROCK, startX, startY, 1, right)
    {}
    
    virtual void doSomething()
    {
        return;
    }
    
    virtual bool blocksMovement() const
    {
        return true;
    }
    
private:
};


class EnergyHolder: public Actor // DONE //
{
public:
    EnergyHolder(int startX, int startY, int imageID, int depth, Direction dir, int health, StudentWorld* world)
    : Actor(world, imageID, startX, startY, depth, dir), m_hitPoints(health), m_food(0) {}
    
    virtual int returnHitPoints() const
    {
        return m_hitPoints;
    }
    
    virtual void changeHealth(int amount)
    {
        m_hitPoints += amount;
    }
    
    void setDead()
    {
        m_hitPoints = 0;
        if (becomesFoodUponDeath())
        {
            dropFood(100);
        }
    }
    
    virtual bool isLiving() const
    {
        return (m_hitPoints > 0);
    }
    
    int returnFoodHeld() const
    {
        return m_food;
    }
    
    void dropFood(int amount);
    
    int pickUpFood(int amount);
    
    int eatFoodFromStorage(int amount);
    
    int pickUpAndEatFood(int amount);
    
    virtual bool becomesFoodUponDeath() const
    {
        return false;
    }
    
private:
    int m_hitPoints;
    int m_food;
    
};

class Pheromone: public EnergyHolder // DONE //
{
public:
    Pheromone(int startX, int startY, int ID, StudentWorld* world, int imageID)
    :EnergyHolder(startX, startY, imageID, 2, right, 256, world), antID(ID)
    {}
    
    virtual void doSomething()
    {
        changeHealth(-1);
    }
    
    virtual bool isPheromone(int colony) const
    {
        if (colony == antID)
            return true;
        else
            return false;
    }
    
    virtual void changeHealth(int amount);
 
private:
    int antID;
    
};

class Anthill: public EnergyHolder // DONE //
{
public:
    Anthill(int startX, int startY, int antNumber, StudentWorld* world, Compiler* compiler)
    :EnergyHolder(startX, startY, IID_ANT_HILL, 2, right, 8999, world), m_compiler(compiler), antID(antNumber)
    {}
    
    virtual void doSomething();
    
    virtual bool isMyAnthill(int colony) const
    {
        if (colony == antID)
            return true;
        else
            return false;
    }
    
    int returnImageID() const;
    
private:
    Compiler* m_compiler;
    int antID;
    
};

class Food: public EnergyHolder // DONE //
{
public:
    Food(int startX, int startY, int health, StudentWorld* world)
    :EnergyHolder(startX, startY, IID_FOOD, 2, right, health, world) {}
    
    virtual void doSomething()
    {
        return;
    }
    
    virtual bool isEdible() const
    {
        return true;
    }
    
private:
    
};

class TriggerablePool: public Actor // DONE //
{
public:
    TriggerablePool(int imageID, int startX, int startY, StudentWorld* world)
    :Actor(world, imageID, startX, startY, 2, right)
    {}
   
    virtual bool isDangerous(int colony) const
    {
        return true;
    }
    
private:
    
    
};

class Water: public TriggerablePool // DONE //
{
public:
    Water(int startX, int startY, StudentWorld* world)
    :TriggerablePool(IID_WATER_POOL, startX, startY, world){}
    
    virtual void doSomething();
    
private:
    
};

class Poison: public TriggerablePool // DONE // 
{
public:
    Poison(int startX, int startY, StudentWorld* world)
    :TriggerablePool(IID_POISON, startX, startY, world) {}
    
    virtual void doSomething();
    
private:
    
};


class Insect: public EnergyHolder
{
public:
    Insect(int imageID, int startX, int startY, int depth, Direction direction, int health, StudentWorld* world)
    :EnergyHolder(startX, startY, imageID, depth, direction, health, world), m_stunCount(0), wasStunned(false)   {}
    
    bool doSomethingInsect();
    
    bool isStunned() const
    {
        return m_stunCount != 0;
    }
    
    virtual void getBitten(int amount)
    {
        changeHealth(-amount);
    }
    
    virtual void getPoisoned()
    {
        changeHealth(-150);
    }
    
    void lowerStun()
    {
        m_stunCount--;
    }
    
    virtual bool becomesFoodUponDeath() const
    {
        return true;
    }
    
    void increaseSleepTicks(int amount)
    {
        m_stunCount += amount;
    }
    
    virtual bool isEnemy(int colony) const
    {
        return true;
    }
    
    virtual void getStunned()
    {
        if (!wasStunned){m_stunCount += 2; wasStunned = true;}
    }
    
    void noLongerStunned()
    {
        wasStunned = false;
    }
    
private:
    int m_stunCount;
    bool wasStunned;
};

class Ant: public Insect
{
public:
    Ant(int antID, int imageID, int startX, int startY, StudentWorld* world, Compiler* compiler)
    :Insect(imageID, startX, startY, 1, randomDirection(), 1500, world), m_compiler(compiler), wasBitten(false), wasBlocked(false), lastRandomNumber(0), instructionCounter(0), antID(antID)
    {}
    
    virtual void doSomething();
    
    virtual bool isEnemy(int colony) const
    {
        if (colony == antID)
            return false;
        else
            return true;
    }
    
    virtual void getBitten(int amount)
    {
        Insect::getBitten(amount);
        wasBitten = true;
    }
    
    int returnPheromoneImageID() const;
    
private:
    Compiler* m_compiler;
    int lastRandomNumber;
    int instructionCounter;
    bool wasBlocked;
    bool wasBitten;
    int antID;
    
    
};


class Grasshopper: public Insect
{
public:
    Grasshopper(int imageID, int startX, int startY, int health, StudentWorld* world)
    :Insect(imageID, startX, startY, 1, randomDirection(), health, world), stepsLeft(chooseSteps())
    {}
    
    int chooseSteps() const
    {
        return randInt(2, 10);
    }
    
    int returnStepsLeft() const
    {
        return stepsLeft;
    }
    
    void lowerStepsleft()
    {
        stepsLeft--;
    }
    void setStepstoZero()
    {
        stepsLeft = 0;
    }
    void setSteps()
    {
        stepsLeft = chooseSteps();
    }
    
    virtual void doSomething();
    
    virtual bool grasshopperAction() = 0;
    
private:
    int stepsLeft;
};

class adultGrasshopper: public Grasshopper
{
public:
    adultGrasshopper(int startX, int startY, StudentWorld* world)
    :Grasshopper(IID_ADULT_GRASSHOPPER, startX, startY, 1600, world)
    {}
    
    virtual bool grasshopperAction();

    virtual void getStunned()
    {
        return;
    }
    
    virtual void getPoisoned()
    {
        return;
    }
    
    virtual void getBitten(int amount);
    
private:
};

class babyGrasshopper: public Grasshopper
{
public:
    babyGrasshopper(int startX, int startY, StudentWorld* world)
    :Grasshopper(IID_BABY_GRASSHOPPER, startX, startY, 500, world)
    {}
    
    virtual bool grasshopperAction();
    
private:
    
};
#endif // ACTOR_H_

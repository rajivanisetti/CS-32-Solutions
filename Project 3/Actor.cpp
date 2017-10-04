#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
static const double PI = 4 * atan(1.0);

bool isPosInBounds(int x, int y);

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

bool isPosInBounds(int x, int y)
{
    if (x <= 0 || x >= 63)
        return false;
    if (y <= 0 || y >= 63)
        return false;
        
    return true;
}

GraphObject::Direction randomDirection()
{
    int a = randInt(0, 3);
    
    if (a == 0)
        return GraphObject::up;
    else if (a == 1)
        return GraphObject::right;
    else if (a == 2)
        return GraphObject::left;
    else
        return GraphObject::down;
}

void EnergyHolder::dropFood(int amount)
{
    Actor* temp = returnWorld()->getEdibleAt(getX(), getY());
    if (temp != nullptr)
    {
        temp->changeHealth(amount);
    }
    else
    {
        returnWorld()->addActor(new Food(getX(), getY(), amount, returnWorld()));
    }
}

void Pheromone::changeHealth(int amount)
{
    if (returnHitPoints() + 256 >= 768)
    {
        EnergyHolder::changeHealth(768 - returnHitPoints());
    }
    else
        EnergyHolder::changeHealth(256);
}



int EnergyHolder::pickUpFood(int amount)
{
    int returnVal = 0;
    int newAmount;
    if (amount + m_food >= 1800)
    {
        newAmount = 1800 - m_food;
    }
    else
    {
        newAmount = amount;
    }
    Actor* temp = returnWorld()->getEdibleAt(getX(), getY());
    if (temp != nullptr)
    {
        if (temp->returnHitPoints() <= newAmount)
        {
            returnVal = returnHitPoints();
            temp->changeHealth(-returnHitPoints());
        }
        else
        {
            returnVal = newAmount;
            temp->changeHealth(-newAmount);
        }
        
        m_food += returnVal;
    }
    
    return returnVal;
}

int EnergyHolder::eatFoodFromStorage(int amount)
{
    if (amount >= m_food)
    {
        changeHealth(m_food);
        int a = m_food;
        m_food = 0;
        return a;
    }
    else
    {
        changeHealth(amount);
        m_food -= amount;
        return amount;
    }
}

int EnergyHolder::pickUpAndEatFood(int amount)
{
    int returnVal = 0;
    Actor* temp = returnWorld()->getEdibleAt(getX(), getY());
    if (temp != nullptr)
    {
        if (temp->returnHitPoints() <= amount)
        {
            returnVal = temp->returnHitPoints();
            temp->changeHealth(-(returnHitPoints()));
        }
        else
        {
            returnVal = amount;
            temp->changeHealth(-amount);
        }
    }

    changeHealth(returnVal);
    
    return returnVal;
}

void Anthill::doSomething()
{
    changeHealth(-1);
    
    if (!isLiving())
    {
        return;
    }
    
    if (pickUpAndEatFood(10000) > 0)
        return;
    
    if (returnHitPoints() >= 2000)
    {
        returnWorld()->addActor(new Ant(antID, returnImageID(), getX(), getY(), returnWorld(), m_compiler));
        changeHealth(-1500);
        returnWorld()->increaseScore(antID);
    }
    
}

void Water::doSomething()       // DONE
{
    returnWorld()->stunAllStunnableAt(getX(), getY());
}

void Poison::doSomething()      // DONE
{
    returnWorld()->poisonAllPoisonableAt(getX(), getY());
}

bool Insect::doSomethingInsect()
{
    changeHealth(-1);
    
    if (!isLiving())
    {
        setDead();
        return true;
    }
    
    if (isStunned())
    {
        lowerStun();
        return true;
    }
    
    return false;
}


void Ant::doSomething()
{
    if (doSomethingInsect())
    {
        return;
    }
    
    for (int commandsExecuted = 0; commandsExecuted < 10;)
    {
        Compiler::Command c;
        
        if (!m_compiler->getCommand(instructionCounter, c))
        {
            setDead();
            return;
        }
        
        if (c.opcode == Compiler::moveForward)
        {
            if (getDirection() == up)
            {
                if (returnWorld()->canMoveTo(getX(), getY() + 1))
                {
                    moveTo(getX(), getY() + 1);
                    wasBlocked = false;
                    wasBitten = false;
                    noLongerStunned();
                }
                else
                {
                    wasBlocked = true;
                }
            }
            if (getDirection() == right)
            {
                if (returnWorld()->canMoveTo(getX() + 1, getY()))
                {
                    moveTo(getX() + 1, getY());
                    wasBlocked = false;
                    wasBitten = false;
                    noLongerStunned();
                }
                else
                {
                    wasBlocked = true;
                }
            }
            if (getDirection() == down)
            {
                if (returnWorld()->canMoveTo(getX(), getY() - 1))
                {
                    moveTo(getX(), getY() - 1);
                    wasBlocked = false;
                    wasBitten = false;
                    noLongerStunned();
                }
                else
                {
                    wasBlocked = true;
                }
            }
            if (getDirection() == left)
            {
                if (returnWorld()->canMoveTo(getX() - 1, getY()))
                {
                    moveTo(getX() - 1, getY());
                    wasBlocked = false;
                    wasBitten = false;
                    noLongerStunned();
                }
                else
                {
                    wasBlocked = true;
                }
            }
            instructionCounter++;
            commandsExecuted++;
            return;
        }
        else if (c.opcode == Compiler::rotateClockwise)
        {
            if (getDirection() == up)
            {
                setDirection(right);
            }
            if (getDirection() == right)
            {
                setDirection(down);
            }
            if (getDirection() == down)
            {
                setDirection(left);
            }
            if (getDirection() == left)
            {
                setDirection(up);
            }
            instructionCounter++;
            commandsExecuted++;
            return;
        }
        else if (c.opcode == Compiler::faceRandomDirection)
        {
            setDirection(randomDirection());
            instructionCounter++;
            commandsExecuted++;
            return;
        }
        else if (c.opcode == Compiler::rotateCounterClockwise)
        {
            if (getDirection() == up)
            {
                setDirection(left);
            }
            if (getDirection() == right)
            {
                setDirection(up);
            }
            if (getDirection() == down)
            {
                setDirection(right);
            }
            if (getDirection() == left)
            {
                setDirection(down);
            }
            instructionCounter++;
            commandsExecuted++;
            return;
        }
        else if (c.opcode == Compiler::bite)    // NOT FINISHED //
        {
            returnWorld()->biteEnemyAt(this, antID, 15);
            instructionCounter++;
            commandsExecuted++;
            return;
        }
        else if (c.opcode == Compiler::eatFood)
        {
            eatFoodFromStorage(100);
            instructionCounter++;
            commandsExecuted++;
            return;
        }
        else if (c.opcode == Compiler::dropFood)
        {
            //dropFood(returnFoodHeld());
            instructionCounter++;
            commandsExecuted++;
            return;
        }
        else if (c.opcode == Compiler::pickupFood)
        {
            pickUpFood(400);
            instructionCounter++;
            commandsExecuted++;
            return;
        }
        else if (c.opcode == Compiler::emitPheromone)
        {
            Actor* pheromone = returnWorld()->getPheromoneAt(getX(), getY(), antID);
            if (pheromone != nullptr)
            {
                pheromone->changeHealth(256);
            }
            else
            {
                returnWorld()->addActor(new Pheromone(getX(), getY(), antID, returnWorld(), returnPheromoneImageID()));
            }
            instructionCounter++;
            commandsExecuted++;
            return;
        }
        else if (c.opcode == Compiler::generateRandomNumber)
        {
            int operand = stoi(c.operand1);
            if (operand == 0)
                lastRandomNumber = 0;
            else
            {
                int rand = randInt(0, operand - 1);
                lastRandomNumber = rand;
            }
            commandsExecuted++;
            instructionCounter++;
        }
        else if (c.opcode == Compiler::goto_command)
        {
            instructionCounter = stoi(c.operand1);
            commandsExecuted++;
        }
        else if (c.opcode == Compiler::if_command)
        {
            if (stoi(c.operand1) == 0)
            {
                if (getDirection() == up)
                {
                    if (returnWorld()->isDangerAt(getX(), getY() + 1, antID))
                    {
                        instructionCounter = stoi(c.operand2);
                    }
                    else instructionCounter++;
                }
                if (getDirection() == right)
                {
                    if (returnWorld()->isDangerAt(getX() + 1, getY(), antID))
                    {
                        instructionCounter = stoi(c.operand2);
                    }
                    else instructionCounter++;
                }
                if (getDirection() == down)
                {
                    if (returnWorld()->isDangerAt(getX(), getY() - 1, antID))
                    {
                        instructionCounter = stoi(c.operand2);
                    }
                    else instructionCounter++;
                }
                if (getDirection() == left)
                {
                    if (returnWorld()->isDangerAt(getX() + 1, getY(), antID))
                    {
                        instructionCounter = stoi(c.operand2);
                    }
                    else instructionCounter++;
                    
                }
            }
            else if (stoi(c.operand1) == 1)
            {
                if (getDirection() == up)
                {
                    if (returnWorld()->getPheromoneAt(getX(), getY() + 1, antID) != nullptr)
                    {
                        instructionCounter = stoi(c.operand2);
                    }
                    else instructionCounter++;
                }
                if (getDirection() == right)
                {
                    if (returnWorld()->getPheromoneAt(getX() + 1, getY(), antID) != nullptr)
                    {
                        instructionCounter = stoi(c.operand2);
                    }
                    else instructionCounter++;
                }
                if (getDirection() == down)
                {
                    if (returnWorld()->getPheromoneAt(getX(), getY() - 1, antID) != nullptr)
                    {
                        instructionCounter = stoi(c.operand2);
                    }
                    else instructionCounter++;
                    
                }
                if (getDirection() == left)
                {
                    if (returnWorld()->getPheromoneAt(getX() - 1, getY(), antID) != nullptr)
                    {
                        instructionCounter = stoi(c.operand2);
                    }
                    else instructionCounter++;
                }
            }
            else if (stoi(c.operand1) == 2)
            {
                if (wasBitten)
                {
                    instructionCounter = stoi(c.operand2);
                }
                else instructionCounter++;
            }
            else if (stoi(c.operand1) == 3)
            {
                if (returnFoodHeld() > 0)
                    instructionCounter = stoi(c.operand2);
                else instructionCounter++;
            }
            else if (stoi(c.operand1) == 4)
            {
                if (returnHitPoints() <= 25)
                {
                    instructionCounter = stoi(c.operand2);
                }
                else instructionCounter++;
            }
            else if (stoi(c.operand1) == 5)
            {
                if (returnWorld()->isAnthillAt(getX(), getY(), antID))
                {
                    instructionCounter = stoi(c.operand2);
                }
                else instructionCounter++;
            }
            else if (stoi(c.operand1) == 6)
            {
                if (returnWorld()->getEdibleAt(getX(), getY()) != nullptr)
                    instructionCounter = stoi(c.operand2);
                
                else instructionCounter++;
            }
            else if (stoi(c.operand1) == 7)
            {
                if (returnWorld()->isEnemyAt(getX(), getY(), antID))
                {
                    instructionCounter = stoi(c.operand2);
                }
                else instructionCounter++;
            }
            else if (stoi(c.operand1) == 8)
            {
                if (wasBlocked)
                {
                    instructionCounter = stoi(c.operand2);
                }
                else instructionCounter++;
            }
            else if (stoi(c.operand1) == 8)
            {
                if (lastRandomNumber == 0)
                    instructionCounter = stoi(c.operand2);
                else instructionCounter++;
            }
            commandsExecuted++;
        }

    }
    
} 


bool babyGrasshopper::grasshopperAction()
{
    if (returnHitPoints() >= 1600)
    {
        returnWorld()->addActor(new adultGrasshopper(getX(), getY(), returnWorld()));

        setDead();
        return true;
    }
    return false;
}

bool adultGrasshopper::grasshopperAction()
{
    int a = randInt(0, 2);
    if (a == 0)
    {
        if (returnWorld()->biteEnemyAt(this, -1, 50))
            return true;
    }
    
    int b = randInt(0, 9);
    {
        if (b == 0)
        {
            for (int k = 0; k < 10; k++)
            {
                double randDegree = randInt(0, 360);
                double radians = ((randDegree/360) * 2 * PI);
                int randX = randInt(-10 * cos(radians), 10 * cos(radians));
                int randY = randInt(-10 * sin(radians), 10 * sin(radians));
                if (isPosInBounds(getX() + randX, getY() + randY) && returnWorld()->canMoveTo(getX() + randX,getY() + randY))
                {
                    moveTo(getX() + randX, getY() + randY);
                    return true;
                }
                
            }
        }
    }
    return false;
}

void Grasshopper::doSomething()
{
    if (doSomethingInsect()) return;
    
    if (grasshopperAction())
    {
        increaseSleepTicks(2);
        return;
    }
    
    if (pickUpAndEatFood(200) > 0)
    {
        if (randInt(0, 1) == 0)
        {
            increaseSleepTicks(2);
            return;
        }
    }
    
    if (returnStepsLeft() == 0)
    {
        setDirection(randomDirection());
        setSteps();
    }
    
    
    if (getDirection() == left)
    {
        if (returnWorld()->StudentWorld::canMoveTo(getX() - 1, getY()))
        {
            moveTo(getX() - 1, getY());
            lowerStepsleft();
            noLongerStunned();
        }
        else
        {
            setStepstoZero();
        }
    }
    if (getDirection() == up)
    {
        if (returnWorld()->StudentWorld::canMoveTo(getX(), getY() + 1))
        {
            moveTo(getX(), getY() + 1);
            lowerStepsleft();
            noLongerStunned();
        }
        else
        {
            setStepstoZero();
        }
        
    }
    if (getDirection() == right)
    {
        if (returnWorld()->StudentWorld::canMoveTo(getX() + 1, getY()))
        {
            moveTo(getX() + 1, getY());
            lowerStepsleft();
            noLongerStunned();
        }
        else
        {
            setStepstoZero();
        }
        
    }
    if (getDirection() == down)
    {
        if (returnWorld()->StudentWorld::canMoveTo(getX(), getY() - 1))
        {
            moveTo(getX(), getY() - 1);
            lowerStepsleft();
            noLongerStunned();
        }
        else
        {
            setStepstoZero();
        }
    }
    
    increaseSleepTicks(2);
    
}

void adultGrasshopper::getBitten(int amount)
{
    EnergyHolder::getBitten(amount);
    if (randInt(0, 1) == 0)
    {
        returnWorld()->biteEnemyAt(this, -1, 50);
    }
}

int Ant::returnPheromoneImageID() const
{
    if (antID == 0)
    {
        return IID_PHEROMONE_TYPE0;
    }
    else if (antID == 1)
    {
        return IID_PHEROMONE_TYPE1;
    }
    else if (antID == 2)
    {
        return IID_PHEROMONE_TYPE2;
    }
    else
    {
        return IID_PHEROMONE_TYPE3;
    }
}

int Anthill::returnImageID() const
{
    if (antID == 0)
    {
        return IID_ANT_TYPE0;
    }
    else if (antID == 1)
    {
        return IID_ANT_TYPE1;
    }
    else if (antID == 2)
    {
        return IID_ANT_TYPE2;
    }
    else
    {
        return IID_ANT_TYPE3;
    }
}

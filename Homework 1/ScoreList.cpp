//
//  ScoreList.cpp
//  Homework 1
//
//  Created by Rajiv Anisetti on 1/21/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//


#include "ScoreList.h"
#include <iostream>
using namespace std;

ScoreList::ScoreList()
{
}

bool ScoreList::add(unsigned long score)
{
    if (score < 0 || score > 100)
        return false;
    
    m_Sequence.insert(score);
    
    return true;
    
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.
}

bool ScoreList::remove(unsigned long score)
{
    return(m_Sequence.erase(m_Sequence.find(score)));
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
}

int ScoreList::size() const
{
    return m_Sequence.size();
    // Return the number of scores in the list.
}

unsigned long ScoreList::minimum() const
{
    if (m_Sequence.empty())
        return NO_SCORE;
    
    unsigned long firstValue;
    m_Sequence.get(0, firstValue);
    
    unsigned long lowestScore = firstValue;
    
    for (int k = 0; k < m_Sequence.size(); k++)
    {
        unsigned long value;
        m_Sequence.get(k, value);
        if (value < lowestScore)
            lowestScore = value;
    }
    
    return lowestScore;
    
    // Return the lowest score in the score list.  If the list is
    // empty, return NO_SCORE.
}

unsigned long ScoreList::maximum() const
{
    if (m_Sequence.empty())
        return NO_SCORE;
    
    unsigned long firstValue;
    m_Sequence.get(0, firstValue);
    
    unsigned long highestScore = firstValue;
    
    for (int k = 0; k < m_Sequence.size(); k++)
    {
        unsigned long value;
        m_Sequence.get(k, value);
        if (value > highestScore)
            highestScore = value;
    }
    
    return highestScore;
// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
} 

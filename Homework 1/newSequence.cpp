//
//  newSequence.cpp
//  Homework 1
//
//  Created by Rajiv Anisetti on 1/21/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

// BUNS CENTRAL //

#include "newSequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence()
{
    arraySequence = new ItemType[DEFAULT_MAX_ITEMS];
    m_Items = 0;
    maxItems = DEFAULT_MAX_ITEMS;
}

Sequence::Sequence(int nItems)
{
    arraySequence = new ItemType[nItems];
    m_Items = 0;
    maxItems = nItems;
}

Sequence::Sequence(Sequence const &s)
{
    arraySequence = new ItemType[s.maxItems];
    for (int k = 0; k < s.m_Items; k++)
    {
        arraySequence[k] = s.arraySequence[k];
    }
    m_Items = s.m_Items;
    maxItems = s.maxItems;
    
}

Sequence::~Sequence()
{
    delete []arraySequence;
}

bool Sequence::empty() const
{
    if (m_Items == 0)
        return true;
    else
        return false;
}

int Sequence::size() const
{
    return m_Items;
}

bool Sequence::insert(int pos, const ItemType &value)
{
    if ((0 > pos) || (pos > size()) || (size() == maxItems))
        return false;
    
    if (empty())
    {
        arraySequence[0] = value;
        m_Items++;
        return true;
    }
    
    if (pos == size())
    {
        arraySequence[pos] = value;
        m_Items++;
        return true;
    }
    
    ItemType temp = arraySequence[size()-1];
    for (int k = pos; k < size() - 1 && k < DEFAULT_MAX_ITEMS - 1; k++)
    {
        arraySequence[k+1] = arraySequence[k];
    }
    arraySequence[pos] = value;
    m_Items++;
    arraySequence[size()-1] = temp;
    return true;
}

int Sequence::insert(const ItemType &value)
{
    int p = 0;
    
    if (empty())
    {
        insert(p, value);
        return p;
    }
    
    for (int k = 0; k < size(); k++)
    {
        if (value <= arraySequence[k])
            break;
        else
            p++;
    }
    
    if (insert(p, value))
        return p;
    
    return -1;
}

bool Sequence::erase(int pos)
{
    if ((0 > pos) || (pos >= size()))
        return false;
    
    for (int k = pos; k < size() - 1; k++)
    {
        arraySequence[k] = arraySequence[k+1];
    }
    m_Items--;
    return true;
}

int Sequence::remove(const ItemType &value)
{
    int nRemoved = 0;
    
    for (int k = 0; k < size(); k++)
    {
        if (arraySequence[k] == value)
        {
            erase(k);
            nRemoved++;
        }
    }
    
    return nRemoved;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if ((0 > pos) || (pos >= size()))
        return false;
    
    value = arraySequence[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if ((0 > pos) || (pos >= size()))
        return false;
    
    arraySequence[pos] = value;
    return true;;
}

int Sequence::find(const ItemType& value) const
{
    for (int k = 0; k < size(); k++)
        if (arraySequence[k] == value)
            return k;
    
    return -1;
}

void Sequence::swap(Sequence& other)
{
    Sequence temp1(*this);
    *this = other;
    other = temp1;
}

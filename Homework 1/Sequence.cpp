//
//  Sequence.cpp
//  Homework 1
//
//  Created by Rajiv Anisetti on 1/19/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#include "Sequence.h"

Sequence::Sequence()
{
    nItems = 0;
}

bool Sequence::empty() const
{
    if (nItems == 0)
        return true;
    else
        return false;
}

int Sequence::size() const
{
    return nItems;
}

bool Sequence::insert(int pos, const ItemType &value)
{
    if ((0 > pos) || (pos > size()))
        return false;
    
    if (empty())
    {
        arraySequence[0] = value;
        nItems++;
        return true;
    }
    
    if (pos == size())
    {
        arraySequence[pos] = value;
        nItems++;
        return true;
    }
    
    ItemType temp = arraySequence[size()-1];
    for (int k = pos; k < size() - 1 && k < DEFAULT_MAX_ITEMS - 1; k++)
    {
        arraySequence[k+1] = arraySequence[k];
    }
    arraySequence[pos] = value;
    nItems++;
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
    nItems--;
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
    ItemType tempArray[DEFAULT_MAX_ITEMS];
    for (int k = 0; k < size(); k++)
        tempArray[k] = arraySequence[k];
    
    int priorSizeA = size();
    int priorSizeB = other.size();
    
    for (int k = 0; k < priorSizeA; k++)
        erase(0);
    
    for (int k = 0; k < priorSizeB; k++)
    {
        ItemType value;
        other.get(k, value);
        insert(k, value);
    }
    
    for (int k = 0; k < priorSizeB; k++)
        other.erase(0);

    for (int k = 0; k < priorSizeA; k++)
        other.insert(k, tempArray[k]);
}


//
//  Sequence.cpp
//  Project 2
//
//  Created by Rajiv Anisetti on 1/27/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#include "Sequence.h"

Sequence::Sequence()
{
    head = nullptr;
    tail = nullptr;
    n_size = 0;
    
    // Initialize Sequence as empty, with head and tail as nullptr. //
}

Sequence::Sequence(const Sequence& other)
{
    head = nullptr;
    tail = nullptr;     // Initialize head and tail as nullptrs to avoid any undefined behavior. //
    
    int pos = 0;
    n_size = 0;
    Node* otherSeq = other.head;
    while (otherSeq != nullptr)     // Loop through other linked list //
    {
        insert(pos, otherSeq->value);      // Insert the values from the other Sequence //
        otherSeq = otherSeq->next;          // Increment other sequence. //
        pos++;                              // Increment this sequence. //
    }
}

Sequence::~Sequence()
{
    Node* n = head;
    while (n != nullptr)            // Loop through and delete every node. //
    {
        Node* d = n;
        n = n->next;
        delete d;
    }
    
    head = nullptr;                     // Avoid possible access to linked list again. //
    tail = nullptr;
}

Sequence& Sequence::operator=(const Sequence& other)
{
    Node* n = head;
    while (n != nullptr)
    {
        Node* d = n;                        // Destructor //
        n = n->next;
        delete d;
    }
    
    head = nullptr;
    tail = nullptr;
    
    int pos = 0;
    n_size = 0;
    Node* otherSeq = other.head;
    while (otherSeq != nullptr)             // Copy Constructor //
    {
        insert(pos, otherSeq->value);
        otherSeq = otherSeq->next;
        pos++;
    }
    return *this;                           // Return value //
}

bool Sequence::empty() const
{
    if (n_size == 0)
        return true;
    
    return false;
}

int Sequence::size() const
{
    return n_size;
}

bool Sequence::insert(int pos, const ItemType& value)
{
    if (0 > pos || pos > size())
        return false;

    if (pos == 0)           // Create head node in this condition //
    {
        Node* p = new Node;
        p->value = value;
        p->next = head;
        p->previous = nullptr;
        head = p;
        if (size() != 0)    // If not only node, connect next node's previous pointer. //
        {
        p->next->previous = p;
        }
        if (pos == size())   // If first node, then head = tail. //
        {
            tail = p;
        }
        n_size++;
        return true;
    }
    
    if (pos == size())      // Create tail node in this condition //
    {
        Node* p = head;
        while (p->next != nullptr)  // Traverse list until last node. //
            p = p->next;
        
        Node *n = new Node;
        n->value = value;           // Assign value. //
        p->next = n;                // Allocate previous and next pointers appropriately. //
        n->previous = p;
        n->next = nullptr;
        tail = n;
        n_size++;
        return true;
    }
    
    if (pos > 0 && pos < size())    // In middle in this condition, no effect on head/tail nodes. //
    {
        Node* p = head;
        for (int k = 0; k < pos - 1; k++)       // Traverse until node before insertion //
        {
            p = p->next;
        }
        Node* n = new Node;
        n->value = value;           // Assign value. //
        n->next = p->next;          // Allocate previous and next pointers appropriately. //
        p->next = n;
        n->next->previous = n;
        n->previous = p;
        n_size++;
        return true;
    }
    
    return true;
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return true if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// (e.g., because it's implemented using a fixed-size array) and is
// full.)  Otherwise, leave the sequence unchanged and return false.
// Notice that if pos is equal to size(), the value is inserted at the
// end.
}

int Sequence::insert(const ItemType& value)
{
    Node* t = head;
    int count = 0;
    while (t != nullptr)        // Traverse linked list. //
    {
        if (t->value > value)   // If value at node is greater than value, insert value before. //
        {
            insert(count, value);
            return count;
        }
        t = t->next;            // Else increment linked list and count. //
        count++;
    }
    
    if (count == size())        // If no value is greater, insert at the end //
        insert(size(), value);
    
    return count;               // Function always works //
    
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
}

bool Sequence::erase(int pos)
{
    if (0 > pos || pos >= size())
        return false;
    
    if (pos == 0 && size() == 1)        // If only one node //
    {
        delete head;                    // Delete node and head/tail pointers, list is empty. //
        head = nullptr;
        tail = nullptr;
        n_size--;                       // Reduce size. //
        return true;
    }
    
    if (pos == 0)                       // Delete beginning of list. //
    {
        Node* n = head;
        head = n->next;                 // Increment head pointer to next. //
        delete n;                       // Delete first element. //
        head->previous = nullptr;
        n_size--;                       // Reduce size. //
        return true;
    }
        
        
    if (pos > 0 && pos < size() - 1)    // Deletion in middle of list. //
    {
        Node* n = head;
        for (int k = 0; k < pos; k++)   // Traverse to node. //
            n = n->next;
    
        n->previous->next = n->next;    // Attach previous and next pointers for surrounding nodes. //
        n->next->previous = n->previous;
        delete n;
        n_size--;                       // Delete and reduce size. //
        return true;
    }
    
    if (pos == size() - 1)              // If position is last. //
    {
        Node* n = tail;
        tail = n->previous;             // Tail becomes second to last node. //
        tail->next = nullptr;           // Tail has no next node. //
        delete n;                       // Delete and reduce size. //
        n_size--;
        return true;
    }
    
    return true;
    
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed this item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
}

int Sequence::remove(const ItemType& value)
{
    int numRemoved = 0;
    while (find(value) != -1)               // While value still exists in list //
    {
            erase(find(value));             // Erase value and increment numRemoved //
            numRemoved++;
    }
    
    return numRemoved;                 // Return value //
    
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (0 > pos || pos >= size())
        return false;
    
    Node* n = head;
    for (int k = 0; k < pos; k++)       // Traverse to node. //
    {
        n = n->next;
    }
    
    value = n->value;                   // Store value. //
    
    return true;
// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (0 > pos || pos >= size())
        return false;
    
    Node* n = head;
    for (int k = 0; k < pos; k++)   // Traverse to node. //
    {
        n = n->next;
    }

    n->value = value;               // Set value. //
    
    return true;
    
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
}

int Sequence::find(const ItemType& value) const
{
    Node* n = head;
    int count = 0;
    while (n != nullptr)            // Traverse linked list. //
    {
        if (n->value == value)      // If value corresponds, return position. //
            return count;
        count++;                    // Else increment count and linked list. //
        n = n->next;
    }
    
    return -1;                      // If value is not found, return -1;
    
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
}

void Sequence::swap(Sequence& other)
{
    Sequence temp(*this);       // Temporary sequence. //
    *this = other;              // Assignment operator //
    other = temp;
    
// Exchange the contents of this sequence with the other one.
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if (seq2.empty() || seq2.size() > seq1.size())      // If second sequence is empty or greater   //
        return -1;                                      //    Return -1                             //
    
    bool Sequence = false;          // Initialize Sequence as not subsequent. //
    ItemType valOne;
    ItemType valTwo;
    int startingPos;
    
    for (int k = 0; k < seq1.size(); k++)       // Traverse through first list. //
    {
        seq1.get(k, valOne);
        seq2.get(0, valTwo);
        if (valOne == valTwo)                   // If value at k seq1 equals first value of seq2 //
        {
            startingPos = k;
            int newPos = k;
            for (int w = 0; w < seq2.size(); w++, newPos++) // Traverse both together from k and 0. //
            {
                Sequence = true;                            // Set sequence to true. //
                seq1.get(newPos, valOne);
                seq2.get(w, valTwo);
                if (valTwo != valOne)
                {
                    Sequence = false;     // If sequence does not match at some point, set Sequence. //
                    break;
                }
            }
            if (Sequence)
                return startingPos;         // If Sequence true, return the starting position. //
        }
    }
    
    return -1;                              // If no subsequence, return -1. //
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence tempResult(result);            // Temporary sequence to avoid aliasing. //
    
    while (!tempResult.empty())
    {
        tempResult.erase(0);                // Clear tempSequence. //
    }
    
    if (seq1.empty())
    {
        tempResult = seq2;
        result = tempResult;
        return;
    }
                                // If either sequence is empty, result is simply other sequence. //
    if (seq2.empty())
    {
        tempResult = seq1;
        result = tempResult;
        return;
    }
    
    int sizeOne = seq1.size();
    int sizeTwo = seq2.size();
    
    int count = 0;
    int oneCount = 0;
    int twoCount = 0;
    
    while (oneCount < sizeOne || twoCount < sizeTwo)    // While larger sequence is not traversed. //
    {
        if (oneCount < sizeOne)                         // If sequence one is not fully traversed. //
        {
            ItemType value;
            seq1.get(oneCount, value);                  // Store value at position oneCount. //
            tempResult.insert(count, value);            // Insert value and increment both lists. //
            oneCount++;
            count++;
        }
        
        if (twoCount < sizeTwo)                         // If sequence two is not fully traversed. //
        {
            ItemType value;
            seq2.get(twoCount, value);
            tempResult.insert(count, value);            // Store value at position twoCount. //
            twoCount++;                                 // Insert value and increment both lists. //
            count++;
        }
        
    }
    
    result = tempResult;                                // Reassign from temporary sequence. //
    return;
}

//
//  Player.hpp
//  PROJECT 1 TEST
//
//  Created by Rajiv Anisetti on 1/12/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include <string>
using namespace std;

class Arena;

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    string dropPoisonPellet();
    string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif /* Player_hpp */

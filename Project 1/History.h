//
//  History.hpp
//  PROJECT 1 TEST
//
//  Created by Rajiv Anisetti on 1/13/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#ifndef History_h
#define History_h
#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows;
    int m_cols;
    int m_display[MAXROWS][MAXCOLS];
};


#endif /* History_hpp */

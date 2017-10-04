//
//  testScoreList.cpp
//  Homework 1
//
//  Created by Rajiv Anisetti on 1/21/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#include "ScoreList.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    ScoreList s;
    assert(s.size() == 0);
    assert(!s.add(-1));
    assert(!s.add(101));
    assert(s.maximum() == NO_SCORE && s.minimum() == NO_SCORE);
    assert(s.add(56) && s.size() == 1 && s.minimum() == 56);
    assert(s.add(57) && s.minimum() == 56 && s.size() == 2);
    assert(s.maximum() == 57);
    assert(s.add(56) && s.size() == 3);
    assert(s.minimum() == 56 && s.maximum() == 57);
    assert(s.add(72) && s.size() == 4);
    assert(s.minimum() == 56 && s.maximum() == 72);
    assert(s.remove(56) && s.minimum() == 56 && s.maximum() == 72);
    assert(s.size() == 3);
    cout << "All tests succeeded" << endl;
}

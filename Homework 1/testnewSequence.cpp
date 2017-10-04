//
//  testnewSequence.cpp
//  Homework 1
//
//  Created by Rajiv Anisetti on 1/21/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

/*
#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find("laobing") == -1);
    s.insert("laobing");
    assert(s.size() == 1  &&  s.find("laobing") == 0);
    s.insert("aaa");
    assert(s.size() == 2  &&  s.find("aaa") == 0);
    s.insert("laobingboass");
    assert(s.size() == 3 && s.find("aaa") == 0);
    assert(s.find("laobing") == 1 && s.find("laobingboass") == 2);
    
    Sequence a;
    assert(a.empty() && a.size() == 00);
    assert(!a.insert(2, "yaes"));
    assert(a.insert(0, "rajiv") && a.find("rajiv") == 0);
    assert(!a.erase(1));
    assert(!a.set(-1, "yard"));
    assert(a.set(0, "lard") && a.find("lard") == 0);
    assert(a.erase(0) && a.find("lard") == -1);
    
    Sequence b;
    assert(b.insert(0, "chump"));
    assert(b.insert("boo") == 0);
    s.swap(b);
    assert(s.size() == 2 && s.find("boo") == 0 && s.find("chump") == 1);
    assert(b.size() == 3 && b.find("aaa") == 0 && b.find("laobingboass") == 2 && b.find("laobing") == 1);
    
    cout << "Passed all tests" << endl;
}

*/


#include "newSequence.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    unsigned long v = 50;
    
    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(k, v));
    
    // Failure if we try to insert a sixth item into b
    assert(!b.insert(5, v));
    
    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    a.swap(b);
    assert(!a.insert(5, v));
    for (int k = 0; k < 1000; k++)
        assert(b.insert(k, v));
    
    cout << "All tests succeeded" << endl;
}


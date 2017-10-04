//
//  testSequence.cpp
//  Homework 1
//
//  Created by Rajiv Anisetti on 1/22/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    s.insert(42);
    assert(s.size() == 1  &&  s.find(42) == 0);
    cout << "Passed all tests" << endl;
}

/*
#include "Sequence.h"
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
assert(s.size() == 3  &&  s.find("laobingboass") == 2);
s.insert(1, "yard");
assert(s.size() == 4 && s.find("yard") == 1 && s.find("aaa") == 0);
assert(s.find("laobing") == 2 && s.find("laobingboass") == 3);

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
assert(b.size() == 4 && b.find("aaa") == 0 && b.find("laobingboass") == 3 && b.find("laobing") == 2);

cout << "Passed all tests" << endl;
}

*/

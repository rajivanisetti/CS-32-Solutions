//
//  main.cpp
//  mazestack
//
//  Created by Rajiv Anisetti on 2/4/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#include <stack>
#include <string>
#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);


class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> istack;
    Coord start(sr, sc);
    istack.push(start);
    maze[sr][sc] = 'X';
    
    while (!istack.empty())
    {
        Coord current = istack.top();
        istack.pop();
        if (current.r() == er && current.c() == ec)
        {
            return true;
        }
        // NORTH //
        
        if ((current.r() - 1 >= 0) && (maze[current.r() - 1][current.c()] != 'X'))
        {
            istack.push(Coord(current.r() - 1, current.c()));
            maze[current.r() - 1][current.c()] = 'X';
        }
        
        // EAST //
        
        if ((current.c() + 1 < nCols) && (maze[current.r()][current.c() + 1] != 'X'))
        {
            istack.push(Coord(current.r(), current.c() + 1));
            maze[current.r()][current.c() + 1] = 'X';
            
        }
        
        // SOUTH //
        
        if ((current.r() + 1 < nRows) && (maze[current.r() + 1][current.c()] != 'X'))
        {
            istack.push(Coord(current.r() + 1, current.c()));
            maze[current.r() + 1][current.c()] = 'X';
            
        }
        
        // WEST //
        
        if ((current.c() - 1 >= 0) && (maze[current.r()][current.c() - 1] != 'X'))
        {
            istack.push(Coord(current.r(), current.c() - 1));
            maze[current.r()][current.c() - 1] = 'X';
            
        }
    }
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 8,8, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}




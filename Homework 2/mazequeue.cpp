//
//  main.cpp
//  mazequeue
//
//  Created by Rajiv Anisetti on 2/5/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#include <queue>
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
    queue<Coord> coordQueue;
    Coord start(sr, sc);
    coordQueue.push(start);
    maze[sr][sc] = 'X';
    
    while (!coordQueue.empty())
    {
        Coord current = coordQueue.front();
        coordQueue.pop();
        if (current.r() == er && current.c() == ec)
        {
            return true;
        }
        // NORTH //
        
        if ((current.r() - 1 >= 0) && (maze[current.r() - 1][current.c()] != 'X'))
        {
            coordQueue.push(Coord(current.r() - 1, current.c()));
            maze[current.r() - 1][current.c()] = 'X';
        }
        
        // EAST //
        
        if ((current.c() + 1 < nCols) && (maze[current.r()][current.c() + 1] != 'X'))
        {
            coordQueue.push(Coord(current.r(), current.c() + 1));
            maze[current.r()][current.c() + 1] = 'X';
            
        }
        
        // SOUTH //
        
        if ((current.r() + 1 < nRows) && (maze[current.r() + 1][current.c()] != 'X'))
        {
            coordQueue.push(Coord(current.r() + 1, current.c()));
            maze[current.r() + 1][current.c()] = 'X';
            
        }
        
        // WEST //
        
        if ((current.c() - 1 >= 0) && (maze[current.r()][current.c() - 1] != 'X'))
        {
            coordQueue.push(Coord(current.r(), current.c() - 1));
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
    
    if (pathExists(maze, 10,10, 6,4, 8,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}



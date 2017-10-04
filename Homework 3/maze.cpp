//
//  main.cpp
//  Homework 3 Q3
//
//  Created by Rajiv Anisetti on 2/10/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = 'X';
    
    if (maze[sr+1][sc] != 'X')
        if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
            return true;
    if (maze[sr-1][sc] != 'X')
        if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
            return true;
    if (maze[sr][sc+1] != 'X')
        if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
            return true;
    if (maze[sr][sc-1] != 'X')
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    
    return false;
}


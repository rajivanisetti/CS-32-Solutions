//
//  support.cpp
//  Project 4
//
//  Created by Rajiv Anisetti on 3/16/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#include <stdio.h>
#include "support.h"


std::string directionOfLine (const GeoSegment& gs)
{
    double angle = angleOfLine(gs);
    if (angle >= 0 && angle <= 22.5)
        return "east";
    if (angle > 22.5 && angle <= 67.5)
        return "northeast";
    if (angle > 67.5 && angle <= 112.5)
        return "north";
    if (angle > 112.5 && angle <= 157.5)
        return "northwest";
    if (angle > 157.5 && angle <= 202.5)
        return "west";
    if (angle > 202.5 && angle <= 247.5)
        return "southwest";
    if (angle > 247.5 && angle <= 292.5)
        return "south";
    if (angle > 292.5 && angle <= 337.5)
        return "southeast";
    else
        return "east";
}

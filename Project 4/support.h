//
//  Header.h
//  Project 4
//
//  Created by Rajiv Anisetti on 3/14/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#ifndef support_h
#define support_h

#include "provided.h"
#include <string>



std::string directionOfLine (const GeoSegment& gs);


inline
bool operator>(const GeoCoord& a, const GeoCoord& b)
{
    if (a.latitude > b.latitude)
        return true;
    else if (b.latitude > a.latitude)
        return false;
    else
        return a.longitude > b.longitude;
}
inline
bool operator==(const GeoCoord& a, const GeoCoord& b)
{
    if (a.latitude == b.latitude && a.longitude == b.longitude)
        return true;
    else
        return false;
}
inline
bool operator<(const GeoCoord& a, const GeoCoord& b)
{
    if (a.latitude < b.latitude)
        return true;
    else if (b.latitude < a.latitude)
        return false;
    else
        return a.longitude < b.longitude;
}
inline
bool operator==(const GeoSegment& a, const GeoSegment& b)
{
    if (a.start == b.start && a.end == b.end)
        return true;
    else
        return false;
}



#endif /* Header_h */

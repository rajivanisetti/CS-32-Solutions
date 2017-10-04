#include "MyMap.h"
#include <iostream>
using namespace std;

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;
    
private:
    MyMap<GeoCoord, vector<StreetSegment>> map;
    int size;
};

SegmentMapperImpl::SegmentMapperImpl()
{
    size = 0;
}

SegmentMapperImpl::~SegmentMapperImpl()
{
    map.clear();
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
    for (int k = 0; k < ml.getNumSegments(); k++)
    {
        StreetSegment temp;
        ml.getSegment(k, temp);

        GeoCoord start = temp.segment.start;
        GeoCoord end = temp.segment.end;
        
        if (map.find(start) == nullptr)
        {
            vector<StreetSegment> listOne;
            listOne.push_back(temp);
            map.associate(start, listOne);
        }
        else
        {
            vector<StreetSegment> listOne = *map.find(start);
            listOne.push_back(temp);
            map.associate(start, listOne);
        }
        
        if (map.find(end) == nullptr)
        {
            vector<StreetSegment> listTwo;
            listTwo.push_back(temp);
            map.associate(end, listTwo);
        }
        else
        {
            vector<StreetSegment> listTwo = *map.find(end);
            listTwo.push_back(temp);
            map.associate(end, listTwo);
        }
        
        if (temp.attractions.size() != 0)
        {
            for (int w = 0; w < temp.attractions.size(); w++)
            {
                GeoCoord coord = temp.attractions[w].geocoordinates;
                if (map.find(coord) == nullptr)
                {
                    vector<StreetSegment> list;
                    list.push_back(temp);
                    map.associate(coord, list);
                }
                else
                {
                    vector<StreetSegment> list = *map.find(coord);
                    list.push_back(temp);
                    map.associate(coord, list);
                }
            }
        }
        
    }
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
    vector<StreetSegment> segments;

    if (map.find(gc) == nullptr)
        return segments;
    else
    {
        return *map.find(gc);
    }
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}

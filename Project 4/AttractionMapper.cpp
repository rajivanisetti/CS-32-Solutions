#include "MyMap.h"
#include <iostream>

class AttractionMapperImpl
{
public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;
    
private:
    MyMap<string,GeoCoord> map;
    int size;
    
};

AttractionMapperImpl::AttractionMapperImpl()
{
    size = 0;
}

AttractionMapperImpl::~AttractionMapperImpl()
{
    map.clear();
}

void AttractionMapperImpl::init(const MapLoader& ml)
{
    for (int k = 0; k < ml.getNumSegments(); k++)
    {
        StreetSegment temp;
        ml.getSegment(k, temp);
        if (temp.attractions.size() != 0)
        {
            for (int w = 0; w < temp.attractions.size(); w++)
            {
                Attraction attr = temp.attractions[w];
                string toLower = "";
                for (int l = 0; l < temp.attractions[w].name.size(); l++)
                {
                    toLower += tolower(temp.attractions[w].name[l]);
                }
                map.associate(toLower, attr.geocoordinates);
            }
        }
        
    }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
    string lowerAttr = "";
    for (int k = 0; k < attraction.size(); k++)
    {
        lowerAttr += tolower(attraction[k]);
    }
    
	if (map.find(lowerAttr) == nullptr)
        return false;
    else
    {
        const GeoCoord* g = map.find(lowerAttr);
        gc = *g;
        return true;
    }
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
	m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
	delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
	return m_impl->getGeoCoord(attraction, gc);
}

#include "provided.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MapLoaderImpl
{
public:
	MapLoaderImpl();
	~MapLoaderImpl();
	bool load(string mapFile);
	size_t getNumSegments() const;
	bool getSegment(size_t segNum, StreetSegment& seg) const;
    
private:
    vector<StreetSegment*> m_list;
    int size;
};

MapLoaderImpl::MapLoaderImpl()
{
    size = 0;
}

MapLoaderImpl::~MapLoaderImpl()
{
    for (int k = 0; k < size; k++)
    {
        delete m_list[k];
    }
}

bool MapLoaderImpl::load(string mapFile)
{
    
    ifstream infile(mapFile);
    if (!infile)
    {
        return false;
    }
    string s;
    
    int counter = 0;
    
    while (getline(infile, s))
    {
        if (counter == 0)
        {
            StreetSegment* temp = new StreetSegment;
            temp->streetName = s;
            m_list.push_back(temp);
            size++;
            counter++;
            continue;
        }
        
        if (counter == 1)
        {
            string startLat = "";
            string startLon = "";
            string endLat = "";
            string endLon = "";
            
            int k = 0;
            while (s[k] != ',' && s[k] != ' ')
            {
                startLat += s[k];
                k++;
            }
            
            k++;
            
            while (s[k] == ' ' || s[k] == ',')
            {
                k++;
            }
            
            while (s[k] != ' ')
            {
                startLon += s[k];
                k++;
            }
            
            k++;
            
            while (s[k] == ' ' || s[k] == ',')
            {
                k++;
            }
            
            while (s[k] != ',')
            {
                endLat += s[k];
                k++;
            }
            
            k++;
            
            while (s[k] == ' ' || s[k] == ',')
            {
                k++;
            }
            
            while (k != s.size())
            {
                endLon += s[k];
                k++;
            }
            
            GeoCoord start = GeoCoord(startLat, startLon);
            GeoCoord end = GeoCoord(endLat, endLon);
            GeoSegment temp = GeoSegment(start, end);
            m_list[size-1]->segment = temp;
            counter++;
            continue;
        }
        
        if (size == 7)
        {
            cout << m_list[6]->segment.start.latitudeText << endl;
            cout << m_list[6]->segment.end.longitudeText << endl;
        }
        
        if (counter == 2)
        {
            int a = stoi(s);
            counter = -1 * a;
            continue;
        }
        
        if (counter < 0)
        {
            string attractionName = "";
            int k = 0;
            while (s[k] != '|')
            {
                attractionName += s[k];
                k++;
            }
            k++;
            string lat = "";
            string lon = "";
            
            while (s[k] == ' ' || s[k] == ',')
            {
                k++;
            }
            
            while (s[k] != ',')
            {
                lat += s[k];
                k++;
            }
            
            k++;
            
            while (s[k] == ' ' || s[k] == ',')
            {
                k++;
            }
            
            while (k < s.size())
            {
                lon += s[k];
                k++;
            }
            
            Attraction temp;
            temp.name = attractionName;
            GeoCoord coord = GeoCoord(lat, lon);
            temp.geocoordinates = coord;
            m_list[size-1]->attractions.push_back(temp);
            counter++;
            continue;
        }
    }
    return true;
}

size_t MapLoaderImpl::getNumSegments() const
{
	return size;
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if (segNum >= 0 && segNum < size -1)
    {
        seg = *m_list[segNum];
        return true;
    }
    else
        return false;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
	m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
	delete m_impl;
}

bool MapLoader::load(string mapFile)
{
	return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
	return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
   return m_impl->getSegment(segNum, seg);
}

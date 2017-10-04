#include "support.h"
#include "MyMap.h"
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct Node
{
    double distance;
    string streetName;
    GeoCoord coord;
    GeoSegment street;
    GeoSegment path;
};

bool operator>(const Node& a, const Node& b)
{
    if (a.distance < b.distance)
        return true;
    else if (a.coord.latitude < b.coord.latitude)
        return true;
    else if (a.coord.longitude < b.coord.longitude)
        return true;
    else
        return false;
}

bool operator<(const Node& a, const Node& b)
{
    if (a.distance > b.distance)
        return true;
    else if (a.coord.latitude > b.coord.latitude)
        return true;
    else if (a.coord.longitude > b.coord.longitude)
        return true;
    else
        return false;
}

bool operator==(const Node& a, const Node& b)
{
    return (a.coord == b.coord);
}



vector<NavSegment> navigateRoute (MyMap<Node, Node>& map, Node* startNode)
{
    vector<NavSegment> vector;
    stack<Node*> stack;
    
    Node* cur = startNode;
    
    while (map.find(*cur)->streetName != "")
    {
        stack.push(cur);
        cur = map.find(*cur);
    }
    
    while (!stack.empty())
    {
        Node current = *stack.top();
        stack.pop();
        
        double distance = distanceEarthMiles(current.path.start, current.path.end);
        
        NavSegment nav = NavSegment(directionOfLine(current.path), current.streetName, distance, current.street);
        
        vector.push_back(nav);
        
        if (!stack.empty())
        {
            
            Node comp = *stack.top();
            if (comp.streetName != current.streetName)
            {
                double differenceofAngles = angleOfLine(comp.street) - angleOfLine(current.street);
                
                string direction;
                
                if (differenceofAngles >= 0 && differenceofAngles <= 180)
                    direction = "left";
                else
                    direction = "right";
                
                
                NavSegment turn = NavSegment(direction, comp.streetName);
                
                vector.push_back(turn);
                
            }
        }
        
            
        
        
        
    }
    
    return vector;
    
}


class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
    
private:
    AttractionMapper m_attractionMapper;
    SegmentMapper m_segmentMapper;
    MapLoader m_mapLoader;
};

NavigatorImpl::NavigatorImpl()
{
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    if (!m_mapLoader.load(mapFile))
        return false;
    else
    {
        m_attractionMapper.init(m_mapLoader);
        m_segmentMapper.init(m_mapLoader);
        return true;
    }
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    if (!directions.empty())
    {
        for (vector<NavSegment>::iterator it = directions.begin(); it != directions.end();)
        {
            it = directions.erase(it);
        }
    }
    
    GeoCoord locStart;
    GeoCoord locEnd;
    if (!m_attractionMapper.getGeoCoord(start, locStart))
    {
        return  NAV_BAD_SOURCE;
    }
    
    if (!m_attractionMapper.getGeoCoord(end, locEnd))
    {
        return NAV_BAD_DESTINATION;
    }

    
    
    
    Node startPoint;
    startPoint.coord = locStart;
    GeoSegment scrap;
    GeoCoord scrapper = GeoCoord("0", "1");
    scrap.start = scrapper;
    scrap.end = scrapper;
    startPoint.street = scrap;
    startPoint.distance = 0;
    
    Node endPoint;
    endPoint.coord = locEnd;
    

    
    MyMap<Node, Node> retraceMap;
    MyMap<Node, bool> checkedMap;
    
    vector<StreetSegment> startstreetSegments = m_segmentMapper.getSegments(locStart);
    
    for (int k = 0; k < startstreetSegments.size(); k++)
    {
        vector<Attraction> attr = startstreetSegments[k].attractions;
        for (int w = 0; w < attr.size(); w++)
        {
            if (attr[w].geocoordinates == locEnd)
            {
                endPoint.street = startstreetSegments[k].segment;
                endPoint.path = startstreetSegments[k].segment;
                endPoint.streetName = startstreetSegments[k].streetName;
                endPoint.distance = distanceEarthMiles(locEnd, locStart);
                retraceMap.associate(endPoint, startPoint);
                directions = navigateRoute(retraceMap, &endPoint);
                return NAV_SUCCESS;
            }
        }
    }
    
    StreetSegment finish = m_segmentMapper.getSegments(locEnd)[0];
    
    priority_queue<Node> myQueue;
    
    myQueue.push(startPoint);
    
    while (!myQueue.empty())
    {
        Node temp = myQueue.top();
        myQueue.pop();
        
        if (checkedMap.find(temp) != nullptr)
            continue;
        
        checkedMap.associate(temp, true);
        
        vector<StreetSegment> streetSegments = m_segmentMapper.getSegments(temp.coord);

        for (int k = 0; k < streetSegments.size(); k++)
        {
            if (!(streetSegments[k].segment == temp.street))
            {
                vector<Attraction> attractions = streetSegments[k].attractions;
                for (int w = 0; w < attractions.size(); w++)
                {
                    if (attractions[w].geocoordinates == locEnd)
                    {
                        endPoint.street = streetSegments[k].segment;
                        GeoSegment path;
                        path.start = temp.coord;
                        path.end = endPoint.coord;
                        endPoint.path = path;
                        endPoint.streetName = streetSegments[k].streetName;
                        endPoint.distance = temp.distance + distanceEarthMiles(locEnd, temp.coord);
                        retraceMap.associate(endPoint, temp);
                        directions = navigateRoute(retraceMap, &endPoint);
                        return NAV_SUCCESS;
                    }
                }
                
                Node beginning;
                beginning.coord = streetSegments[k].segment.start;
                if (!(beginning.coord == temp.coord) && retraceMap.find(beginning) == nullptr)
                {
                    beginning.street = streetSegments[k].segment;
                    beginning.distance = temp.distance + distanceEarthMiles(temp.coord, beginning.coord);
                    GeoSegment firstPath;
                    firstPath.start = temp.coord;
                    firstPath.end = beginning.coord;
                    beginning.path = firstPath;
                    beginning.streetName = streetSegments[k].streetName;
                    myQueue.push(beginning);
                    retraceMap.associate(beginning, temp);
                }
        
                
                Node end;
                end.coord = streetSegments[k].segment.end;
                if (!(end.coord == temp.coord) && retraceMap.find(end) == nullptr)
                {
                    end.street = streetSegments[k].segment;
                    end.distance = temp.distance + distanceEarthMiles(temp.coord, end.coord);
                    GeoSegment secondPath;
                    secondPath.start = temp.coord;
                    secondPath.end = end.coord;
                    end.path = secondPath;
                    end.streetName = streetSegments[k].streetName;
                    myQueue.push(end);
                    retraceMap.associate(end, temp);
                }
            }
            
        }
        
        
    }
    
    if (myQueue.empty())
        return NAV_NO_ROUTE;
    
    
    

        
	return NAV_SUCCESS;  // This compiles, but may not be correct
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}

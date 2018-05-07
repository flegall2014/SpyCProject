// Application
#include "waypoint.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

WayPoint::WayPoint()
{

}

//-------------------------------------------------------------------------------------------------

WayPoint::WayPoint(const QGeoCoordinate &geoCoord, const Type &eType) : m_geoCoord(geoCoord), m_eType(eType)
{

}

//-------------------------------------------------------------------------------------------------

WayPoint::~WayPoint()
{

}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &WayPoint::geoCoord() const
{
    return m_geoCoord;
}

//-------------------------------------------------------------------------------------------------

const WayPoint::Type &WayPoint::type() const
{
    return m_eType;
}

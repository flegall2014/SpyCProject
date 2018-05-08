// Application
#include "waypoint.h"

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

void WayPoint::setGeoCoord(const QGeoCoordinate &geoCoord)
{
    m_geoCoord = geoCoord;
}

//-------------------------------------------------------------------------------------------------

const WayPoint::Type &WayPoint::type() const
{
    return m_eType;
}

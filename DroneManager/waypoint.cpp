// Application
#include "waypoint.h"
using namespace  Model;

//-------------------------------------------------------------------------------------------------

WayPoint::WayPoint()
{
    qRegisterMetaType<WayPoint>("WayPoint");
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

//-------------------------------------------------------------------------------------------------

void WayPoint::setType(const Type &eType, bool bClockWise)
{
    m_eType = eType;
}

//-------------------------------------------------------------------------------------------------

int WayPoint::speed() const
{
    return (int)m_eSpeed;
}

//-------------------------------------------------------------------------------------------------

void WayPoint::setSpeed(int iSpeed)
{
    m_eSpeed = (Speed)iSpeed;
}

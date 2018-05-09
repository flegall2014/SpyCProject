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

//-------------------------------------------------------------------------------------------------

void WayPoint::setType(const Type &eType, bool bClockWise)
{
    m_eType = eType;
    setDefaultMetaDataForType(m_eType, bClockWise);
}

//-------------------------------------------------------------------------------------------------

void WayPoint::setDefaultMetaDataForType(const Type &eType, bool bClockWise)
{
    m_mMetaData.clear();
    if (eType == LOITER)
    {
        m_mMetaData[RADIUS] = 300;
        m_mMetaData[CLOCKWISE] = bClockWise;
    }
    else
    if (eType == EIGHT)
    {
        m_mMetaData[RADIUS] = 300;
        m_mMetaData[LENGTH] = 300;
        m_mMetaData[CLOCKWISE] = bClockWise;
    }
    else
    if (eType == HIPPODROM)
    {
        m_mMetaData[RADIUS] = 300;
        m_mMetaData[LENGTH] = 300;
        m_mMetaData[CLOCKWISE] = bClockWise;
    }
}

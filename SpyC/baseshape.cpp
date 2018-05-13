// Qt
#include <QDebug>

// Application
#include "baseshape.h"
#define BASE_INCREMENT 100

//-------------------------------------------------------------------------------------------------

BaseShape::BaseShape(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

BaseShape::~BaseShape()
{

}

//-------------------------------------------------------------------------------------------------

QGeoCoordinate BaseShape::computeCenter() const
{
    if (m_path.size() > 0)
    {
        double dTotalLat = 0, dTotalLon = 0;
        for (int i=0; i<m_path.size(); i++)
        {
            dTotalLat += m_path.coordinateAt(i).latitude();
            dTotalLon += m_path.coordinateAt(i).longitude();
        }
        return QGeoCoordinate(dTotalLat/m_path.size(), dTotalLon/m_path.size());
    }

    return QGeoCoordinate();
}

//-------------------------------------------------------------------------------------------------

void BaseShape::rotate(double dAngle)
{
    for (int i=0; i<m_path.size(); i++)
    {
        // Read current coord
        QGeoCoordinate currentCoord = m_path.coordinateAt(i);

        // Read point distance to center
        double dDistance = m_center.distanceTo(currentCoord);

        // Compute point azimuth
        double dAzimuth = m_center.azimuthTo(currentCoord);

        // Increment by angle
        dAzimuth += dAngle;

        // New coord
        QGeoCoordinate newCoord = m_center.atDistanceAndAzimuth(dDistance, dAzimuth);

        // Update point
        m_path.replaceCoordinate(i, newCoord);
    }

    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void BaseShape::moveTo(const QGeoCoordinate &pos)
{
    for (int i=0; i<m_path.size(); i++)
    {
        // Read current coord
        QGeoCoordinate currentCoord = m_path.coordinateAt(i);

        // Read point distance to center
        double dDistance = m_center.distanceTo(currentCoord);

        // Compute point azimuth
        double dAzimuth = m_center.azimuthTo(currentCoord);

        // Update point
        m_path.replaceCoordinate(i, pos.atDistanceAndAzimuth(dDistance, dAzimuth));
    }

    // Update pos
    m_center = pos;

    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void BaseShape::rescale(int iIncrement)
{
    bool bUpScale = iIncrement >= 0;
    for (int i=0; i<m_path.size(); i++)
    {
        // Read current coord
        QGeoCoordinate currentCoord = m_path.coordinateAt(i);

        // Read point distance to center
        double dDistance = m_center.distanceTo(currentCoord);

        // Compute point azimuth
        double dAzimuth = m_center.azimuthTo(currentCoord);

        // Update point
        m_path.replaceCoordinate(i, m_center.atDistanceAndAzimuth(dDistance+(bUpScale ? BASE_INCREMENT : -BASE_INCREMENT), dAzimuth));
    }

    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void BaseShape::setLatitudeAtIndex(int iIndex, double dLatitude)
{
    if ((iIndex >= 0) && (iIndex < m_path.size()))
    {
        QGeoCoordinate currentCoordinate = m_path.coordinateAt(iIndex);
        currentCoordinate.setLatitude(dLatitude);
        m_path.replaceCoordinate(iIndex, currentCoordinate);
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

void BaseShape::setLongitudeAtIndex(int iIndex, double dLatitude)
{
    if ((iIndex >= 0) && (iIndex < m_path.size()))
    {
        QGeoCoordinate currentCoordinate = m_path.coordinateAt(iIndex);
        currentCoordinate.setLongitude(dLatitude);
        m_path.replaceCoordinate(iIndex, currentCoordinate);
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

void BaseShape::setAltitudeAtIndex(int iIndex, double dAltitude)
{
    if ((iIndex >= 0) && (iIndex < m_path.size()))
    {
        QGeoCoordinate currentCoordinate = m_path.coordinateAt(iIndex);
        currentCoordinate.setAltitude(dAltitude);
        m_path.replaceCoordinate(iIndex, currentCoordinate);
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QGeoPath &BaseShape::path() const
{
    return m_path;
}

//-------------------------------------------------------------------------------------------------

int BaseShape::count() const
{
    return m_path.size();
}

//-------------------------------------------------------------------------------------------------

int BaseShape::type() const
{
    return (int)m_eType;
}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &BaseShape::center() const
{
    return m_center;
}

//-------------------------------------------------------------------------------------------------

RectangleShape::RectangleShape(QObject *pParent) : BaseShape(pParent)
{
    m_eType = RECTANGLE;
}

//-------------------------------------------------------------------------------------------------

RectangleShape::RectangleShape(const QGeoCoordinate &topLeft, const QGeoCoordinate &bottomRight, QObject *pParent) :
    BaseShape(pParent)
{
    m_eType = RECTANGLE;
    m_path.addCoordinate(topLeft);
    m_path.addCoordinate(QGeoCoordinate(bottomRight.latitude(), topLeft.longitude()));
    m_path.addCoordinate(bottomRight);
    m_path.addCoordinate(QGeoCoordinate(topLeft.latitude(), bottomRight.longitude()));
    m_center = computeCenter();
}

//-------------------------------------------------------------------------------------------------

RectangleShape::~RectangleShape()
{

}

//-------------------------------------------------------------------------------------------------

QGeoCoordinate RectangleShape::topLeft() const
{
    if (!m_path.isEmpty())
        return m_path.coordinateAt(0);
    return QGeoCoordinate();
}

//-------------------------------------------------------------------------------------------------

QGeoCoordinate RectangleShape::bottomRight() const
{
    if (m_path.size() > 2)
        return m_path.coordinateAt(2);
    return QGeoCoordinate();
}

//-------------------------------------------------------------------------------------------------

CircleShape::CircleShape(QObject *pParent) : BaseShape(pParent)
{
    m_eType = CIRCLE;
}

//-------------------------------------------------------------------------------------------------

CircleShape::CircleShape(const QGeoCoordinate &center, double dRadius, QObject *pParent) : BaseShape(pParent),
    m_dRadius(dRadius)
{
    m_eType = CIRCLE;
    m_center = center;
}

//-------------------------------------------------------------------------------------------------

CircleShape::~CircleShape()
{

}

//-------------------------------------------------------------------------------------------------

double CircleShape::radius() const
{
    return m_dRadius;
}

//-------------------------------------------------------------------------------------------------

void CircleShape::rotate(double dAngle)
{
    // No op
    Q_UNUSED(dAngle);
}

//-------------------------------------------------------------------------------------------------

void CircleShape::rescale(int iIncrement)
{
    bool bUpScale = iIncrement >= 0;
    m_dRadius += (bUpScale ? BASE_INCREMENT : -BASE_INCREMENT);
    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

TriangleShape::TriangleShape(QObject *pParent) : BaseShape(pParent)
{
    m_eType = TRIANGLE;
}

//-------------------------------------------------------------------------------------------------

TriangleShape::TriangleShape(const QGeoCoordinate &point1, const QGeoCoordinate &point2, const QGeoCoordinate &point3, QObject *pParent) :
    BaseShape(pParent)
{
    m_eType = TRIANGLE;
    m_path.addCoordinate(point1);
    m_path.addCoordinate(point2);
    m_path.addCoordinate(point3);
    m_center = computeCenter();
}

//-------------------------------------------------------------------------------------------------

TriangleShape::~TriangleShape()
{

}

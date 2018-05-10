// Qt
#include <QRectF>

// Application
#include "baseshape.h"
#define SIZE_INCREMENT
//-------------------------------------------------------------------------------------------------

BaseShape::BaseShape(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

BaseShape::BaseShape(const Type &eType, QObject *pParent) : QObject(pParent),
    m_eType(eType)
{

}

//-------------------------------------------------------------------------------------------------

BaseShape::~BaseShape()
{

}

//-------------------------------------------------------------------------------------------------

int BaseShape::type() const
{
    return (int)m_eType;
}

//-------------------------------------------------------------------------------------------------

bool BaseShape::selected() const
{
    return m_bSelected;
}

//-------------------------------------------------------------------------------------------------

void BaseShape::select(bool bSelected)
{
    m_bSelected = bSelected;
    emit selectedChanged();
}

//-------------------------------------------------------------------------------------------------

void BaseShape::setPosition(const QGeoCoordinate &position)
{
    Q_UNUSED(position);
}

//-------------------------------------------------------------------------------------------------

QList<QGeoCoordinate> BaseShape::boundingRect() const
{
    return QList<QGeoCoordinate>();
}

//-------------------------------------------------------------------------------------------------

RectShape::RectShape(QObject *pParent) : BaseShape(RECTANGLE, pParent)
{

}

//-------------------------------------------------------------------------------------------------

RectShape::RectShape(const QGeoCoordinate &topLeft, const QGeoCoordinate &bottomRight, QObject *pParent) :
    BaseShape(RECTANGLE, pParent), m_topLeft(topLeft), m_bottomRight(bottomRight)
{

}

//-------------------------------------------------------------------------------------------------

RectShape::~RectShape()
{

}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &RectShape::topLeft() const
{
    return m_topLeft;
}

//-------------------------------------------------------------------------------------------------

void RectShape::setTopLeft(const QGeoCoordinate &topLeft)
{
    m_topLeft = topLeft;
    emit topLeftChanged();
}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &RectShape::bottomRight() const
{
    return m_bottomRight;
}

//-------------------------------------------------------------------------------------------------

void RectShape::setBottomRight(const QGeoCoordinate &bottomRight)
{
    m_bottomRight = bottomRight;
    emit bottomRightChanged();
}

//-------------------------------------------------------------------------------------------------

QList<QGeoCoordinate> RectShape::boundingRect() const
{
    QList<QGeoCoordinate> boundingRect;
    boundingRect << m_topLeft << m_bottomRight;
    return boundingRect;
}

//-------------------------------------------------------------------------------------------------

CircleShape::CircleShape(QObject *pParent) : BaseShape(CIRCLE, pParent)
{

}

//-------------------------------------------------------------------------------------------------

CircleShape::CircleShape(const QGeoCoordinate &center, double dRadius, QObject *pParent) :
    BaseShape(CIRCLE, pParent), m_center(center), m_dRadius(dRadius)
{

}

//-------------------------------------------------------------------------------------------------

CircleShape::~CircleShape()
{

}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &CircleShape::center() const
{
    return m_center;
}

//-------------------------------------------------------------------------------------------------

void CircleShape::setCenter(const QGeoCoordinate &center)
{
    m_center = center;
    emit centerChanged();
}

//-------------------------------------------------------------------------------------------------

double CircleShape::radius() const
{
    return m_dRadius;
}

//-------------------------------------------------------------------------------------------------

void CircleShape::setRadius(double dRadius)
{
    m_dRadius = dRadius;
    emit radiusChanged();
}

//-------------------------------------------------------------------------------------------------

void CircleShape::setPosition(const QGeoCoordinate &position)
{
    setCenter(position);
}

//-------------------------------------------------------------------------------------------------

QList<QGeoCoordinate> CircleShape::boundingRect() const
{
    QGeoCoordinate topLeft = m_center.atDistanceAndAzimuth(m_dRadius, 135);
    QGeoCoordinate bottomRight = m_center.atDistanceAndAzimuth(m_dRadius, 135+180);
    QList<QGeoCoordinate> boundingRect;
    boundingRect << topLeft << bottomRight;
    return boundingRect;
}

//-------------------------------------------------------------------------------------------------

TriangleShape::TriangleShape(QObject *pParent) : BaseShape(TRIANGLE, pParent)
{

}

//-------------------------------------------------------------------------------------------------

TriangleShape::TriangleShape(const QGeoCoordinate &point1, const QGeoCoordinate &point2, const QGeoCoordinate &point3, QObject *pParent) :
    BaseShape(TRIANGLE, pParent), m_point1(point1), m_point2(point2), m_point3(point3)
{

}

//-------------------------------------------------------------------------------------------------

TriangleShape::~TriangleShape()
{

}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &TriangleShape::point1() const
{
    return m_point1;
}

//-------------------------------------------------------------------------------------------------

void TriangleShape::setPoint1(const QGeoCoordinate &point)
{
    m_point1 = point;
    emit point1Changed();
}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &TriangleShape::point2() const
{
    return m_point2;
}

//-------------------------------------------------------------------------------------------------

void TriangleShape::setPoint2(const QGeoCoordinate &point)
{
    m_point2 = point;
    emit point2Changed();
}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &TriangleShape::point3() const
{
    return m_point3;
}

//-------------------------------------------------------------------------------------------------

void TriangleShape::setPoint3(const QGeoCoordinate &point)
{
    m_point3 = point;
    emit point3Changed();
}

//-------------------------------------------------------------------------------------------------

QList<QGeoCoordinate> TriangleShape::boundingRect() const
{
    double dMinLatitude = qMin(m_point1.latitude(), m_point2.latitude());
    dMinLatitude = qMin(dMinLatitude, m_point3.latitude());
    double dMaxLatitude = qMax(m_point1.latitude(), m_point2.latitude());
    dMaxLatitude = qMax(dMinLatitude, m_point3.latitude());

    double dMinLongitude = qMin(m_point1.longitude(), m_point2.longitude());
    dMinLongitude = qMin(dMinLongitude, m_point3.longitude());
    double dMaxLongitude = qMax(m_point1.longitude(), m_point2.longitude());
    dMaxLongitude = qMax(dMaxLongitude, m_point3.longitude());

    QGeoCoordinate topLeft(dMinLatitude, dMinLongitude);
    QGeoCoordinate bottomRight(dMaxLatitude, dMaxLongitude);

    QList<QGeoCoordinate> boundingRect;
    boundingRect << topLeft << bottomRight;

    return boundingRect;
}

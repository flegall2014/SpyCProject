#ifndef WAYPOINT_H
#define WAYPOINT_H

// Qt
#include <QGeoCoordinate>

class WayPoint
{
    Q_ENUMS(Type)

public:
    enum Type {POINT, LOITER, EIGHT, HIPPODROM};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    WayPoint();

    //! Constructor
    WayPoint(const QGeoCoordinate &geoCoord, const Type &eType=POINT);

    //! Destructor
    virtual ~WayPoint();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return geoCoord
    const QGeoCoordinate &geoCoord() const;

    //! Set geoCoord
    void setGeoCoord(const QGeoCoordinate &geoCoord);

    //! Return type
    const Type &type() const;

private:
    //! Geo coordinate
    QGeoCoordinate m_geoCoord;

    //! Point type
    Type m_eType = POINT;
};

#endif // WAYPOINT_H

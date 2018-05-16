#ifndef WAYPOINT_H
#define WAYPOINT_H

// Qt
#include <QGeoCoordinate>
#include <QVector>
#include <QMap>
#include <QVariant>

// Application
#include "drone_manager_global.h"

namespace Model {
class DRONEMANAGERSHARED_EXPORT WayPoint
{
    Q_ENUMS(Type)

public:
    enum Type {POINT=Qt::UserRole+1, LOITER, EIGHT, HIPPODROM};
    enum Speed {ECO=Qt::UserRole+1, OBSERVATION, FAST};

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

    //! Set type
    void setType(const Type &eType, bool bClockWise=true);

    //! Return speed
    int speed() const;

    //! Set speed
    void setSpeed(int iSpeed);

private:
    //! Geo coordinate
    QGeoCoordinate m_geoCoord;

    //! Point type
    Type m_eType = POINT;

    //! Point metadata
    QMap<int, QVariant> m_mMetaData;

    //! Speed
    Speed m_eSpeed = ECO;
};
}

typedef QVector<Model::WayPoint> WayPointList;
Q_DECLARE_METATYPE(Model::WayPoint::Type)

#endif // WAYPOINT_H

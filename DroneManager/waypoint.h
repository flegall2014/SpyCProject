#ifndef WAYPOINT_H
#define WAYPOINT_H

// Qt
#include <QGeoCoordinate>
#include <QVariantMap>

// Application
#include "drone_manager_global.h"

namespace Model {
class DRONEMANAGERSHARED_EXPORT WayPoint
{
    Q_ENUMS(Type)

public:
    enum Type {POINT, LOITER, EIGHT, HIPPODROM};
    enum MetaData {
        // Loiter
        RADIUS,

        // Eight / Hippodrom
        ANGLE,
        LENGTH,

        // Clock wise?
        CLOCKWISE
    };

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

    //! Set default meta data for type
    void setDefaultMetaDataForType(const Type &eType, bool bClockWise=true);

private:
    //! Geo coordinate
    QGeoCoordinate m_geoCoord;

    //! Point type
    Type m_eType = POINT;

    //! Point metadata
    QMap<int, QVariant> m_mMetaData;
};
}

Q_DECLARE_METATYPE(Model::WayPoint::Type)

#endif // WAYPOINT_H

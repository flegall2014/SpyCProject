#ifndef FLIGHTSIMULATOR_H
#define FLIGHTSIMULATOR_H

// Qt
#include <QObject>
#include <QGeoCoordinate>
#include <QGeoPath>
#include <QVector>
#include <QTimer>

// Application
#include "basesimulator.h"
#include "drone_manager_global.h"

namespace Model {
class DRONEMANAGERSHARED_EXPORT FlightSimulator : public BaseSimulator
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    FlightSimulator(const QString &sDroneUID, QObject *pParent=nullptr);

    //! Destructor
    ~FlightSimulator();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Compute points
    void computeFlightPath(const QGeoPath &geoPath, int iPointCount=100);

    //! Play
    virtual void start();

    //! Stop
    virtual void stop();

private:
    //! Detailed path
    QVector<QGeoCoordinate> m_vDetailedPath;

    //! Heading
    QVector<double> m_vHeading;

    //! Timer
    QTimer m_timer;

    //! Point index
    int m_iPointIndex = 0;

public slots:
    //! Time out
    void onTimeOut();

signals:
    //! PositionChanged
    void positionChanged(const QGeoCoordinate &geoCoord, double dHeading, const QString &sDroneUID);
};
}

#endif // FLIGHTSIMULATOR_H

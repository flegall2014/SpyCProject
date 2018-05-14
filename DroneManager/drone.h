#ifndef DRONE_H
#define DRONE_H

// Qt
#include <QObject>
#include <QTimer>
#include <QGeoCoordinate>
#include <QGeoPath>
#include <QVector>

// Application
#include "drone_manager_global.h"
#include "waypoint.h"

namespace Model {
class FlightSimulator;
class BatterySimulator;
class GPSSimulator;
class DRONEMANAGERSHARED_EXPORT Drone : public QObject
{
    Q_OBJECT

public:
    //! Drone error
    enum DroneError {NO_SAFETY=Qt::UserRole+1, NO_LANDING_PLAN, NO_MISSION_PLAN};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    Drone(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPos, QObject *pParent=nullptr);

    //! Destructor
    virtual ~Drone();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return drone uid
    const QString &uid() const;

    //! Return drone video url
    const QString &videoUrl() const;

    //! Return initial pos
    const QGeoCoordinate &initialPosition() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Set safety
    void setSafety(const QVector<WayPoint> &geoPath);

    //! Set mission plan
    void setMissionPlan(const QVector<WayPoint> &geoPath);

    //! Set landing plan
    void setLandingPlan(const QVector<WayPoint> &geoPath);

    //! Set exclusion area
    void setExclusionArea(const QList<QGeoPath> &lExclusionArea);

    //! Take off
    void takeOff();

    //! Fail safe
    void failSafe();

private:
    //! UID
    QString m_sDroneUID = "";

    //! Video url
    QString m_sVideoUrl = "";

    //! Initial position
    QGeoCoordinate m_initialPosition;

    //! Safety
    QVector<WayPoint> m_safety;

    //! Mission plan
    QVector<WayPoint> m_missionPlan;

    //! Landing plan
    QVector<WayPoint> m_landingPlan;

    //! Exclusion area
    QList<QGeoPath> m_lExclusionArea;

    //! Flight simulator
    FlightSimulator *m_pFlightSimulator = nullptr;

    //! Battery simulator
    BatterySimulator *m_pBatterySimulator = nullptr;

    //! GPS simulator
    GPSSimulator *m_pGPSSimulator;

public slots:
    //! Position changed
    void onPositionChanged(const QGeoCoordinate &geoCoord, double dHeading);

signals:
    //! Position changed
    void positionChanged(const QGeoCoordinate &geoCoord, double dHeading, const QString &sDroneUID);

    //! Battery level changed
    void batteryLevelChanged(int iBatteryLevel, const QString &sDroneUID);

    //! GPS strength changed
    void gpsStrengthChanged(int iGPSStrength, const QString &sDroneUID);

    //! Mission plan changed
    void missionPlanChanged(const QString &sDroneUID);

    //! Safety changed
    void safetyChanged(const QString &sDroneUID);

    //! Landing plan changed
    void landingPlanChanged(const QString &sDroneUID);

    //! Exclusion area changed
    void exclusionAreaChanged(const QString &sDroneUID);

    //! Drone error
    void droneError(const Drone::DroneError &eDroneError, const QString &sDroneUID);

    //! Fail safe
    void failSafeDone(const QString &sDroneUID);
};
}

#endif // DRONE_H

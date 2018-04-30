#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

// Qt
#include <QObject>
#include <QVector>
#include <QTimer>
#include <QHash>
#include <QGeoPath>

// Application
#include "drone_manager_global.h"
#include "drone.h"
#include <ibaseplugin.h>

namespace Model {
class Drone;
class DRONEMANAGERSHARED_EXPORT DroneManager : public IBasePlugin
{
    Q_OBJECT
    Q_INTERFACES(IBasePlugin)
    Q_PLUGIN_METADATA(IID "com.tosa.DroneManager")

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    DroneManager(QObject *pParent=nullptr);

    //! Destructor
    ~DroneManager();

    //-------------------------------------------------------------------------------------------------
    // IBasePlugin interface
    //-------------------------------------------------------------------------------------------------

    //! Return plugin name
    virtual QString name() const;

    //! Return version
    virtual float version() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Set mission plan
    void setMissionPlan(const QString &sDroneUID, const QGeoPath &missionPlan);

    //! Set safety
    void setSafety(const QString &sDroneUID, const QGeoPath &safety);

private:
    //! Drone timer
    QTimer m_droneTimer;

    //! Drones
    QHash<QString, Drone *> m_hDrones;

public slots:
    //! Start drone detection
    void onStartDroneDetection();

    //! Drone time out
    void onDroneTimeOut();

    //! Take off drone
    void onTakeOffRequest(const QString &DroneUID);

    //! Fail safe
    void onFailSafeRequest(const QString &DroneUID);

    //! Upload mission plan
    void onUploadMissionPlan(const QGeoPath &path, const QString &sDroneUID);

    //! Upload safety
    void onUploadSafety(const QGeoPath &path, const QString &sDroneUID);

signals:
    //! New drone available
    void newDroneAvailable(const QString &sVideoUrl, const QGeoCoordinate &initialPosition, const QString &sDroneUID);

    //! Position changed
    void positionChanged(const QGeoCoordinate &position, double dHeading, const QString &sDroneUID);

    //! Battery level changed
    void batteryLevelChanged(int iBatteryLevel, const QString &sDroneUID);

    //! GPS strength changed
    void gpsStrengthChanged(int iGPSStrength, const QString &sDroneUID);

    //! Mission plan changed
    void missionPlanChanged(const QString &sDroneUID);

    //! Safety changed
    void safetyChanged(const QString &sDroneUID);

    //! Drone error
    void droneError(const Drone::DroneError &eError, const QString &sDroneUID);

    //! Fail safe fone
    void failSafeDone(const QString &sDroneUID);
};
}

#endif // DRONEMANAGER_H

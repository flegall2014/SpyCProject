#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

// Qt
#include <QObject>
class QQuickItem;

// Application
#include "iservice.h"
#include "dronebase.h"
#include <dronemanager.h>
#include <alert.h>
class DroneModel;
namespace Model {
class DroneManager;
}
class MissionPlanController;
class FlightController;
class SettingController;
class BatteryController;
class GPSController;

class MasterController : public QObject, public IService
{
    Q_OBJECT
    Q_PROPERTY(DroneModel *droneModel READ droneModel NOTIFY droneModelChanged)
    Q_PROPERTY(MissionPlanController *missionPlanController READ missionPlanController NOTIFY missionPlanControllerChanged)
    Q_PROPERTY(FlightController *flightController READ flightController NOTIFY flightControllerChanged)
    Q_PROPERTY(SettingController *settingController READ settingController NOTIFY settingControllerChanged)
    Q_PROPERTY(BatteryController *batteryController READ batteryController NOTIFY batteryControllerChanged)
    Q_PROPERTY(GPSController *gpsController READ gpsController NOTIFY gpsControllerChanged)
    Q_PROPERTY(DroneBase *currentDrone READ currentDrone WRITE setCurrentDrone NOTIFY currentDroneChanged)
    Q_PROPERTY(QString applicationTitle READ applicationTitle WRITE setApplicationTitle NOTIFY applicationTitleChanged)
    Q_ENUMS(DroneError)

public:
    friend class SpyC;
    friend class MissionPlanController;
    friend class FlightController;
    friend class SettingController;
    friend class BatteryController;
    friend class GPSController;

    //! Drone error
    enum DroneError {NO_SAFETY=Qt::UserRole+1, NO_MISSION_PLAN};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    MasterController(QObject *pParent=nullptr);

    //! Destructor
    virtual ~MasterController();

    //-------------------------------------------------------------------------------------------------
    // IService interface
    //-------------------------------------------------------------------------------------------------

    //! Startup
    virtual bool startup(const QStringList &lArgs=QStringList());

    //! Shutdown
    virtual void shutdown();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Set model
    void setModel(Model::DroneManager *pDroneManager);

    //! Detect drones
    Q_INVOKABLE void detectDrones();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Set current drone
    void setCurrentDrone(DroneBase *pCurrentDrone);

    //! Return current drone
    DroneBase *currentDrone() const;

    //! Set application title
    void setApplicationTitle(const QString &sApplicationTitle);

    //! Return application title
    const QString &applicationTitle() const;

    //! Set dialog manager
    void setDialogMgr(QQuickItem *pDialogMgr);

private:
    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return drone model view
    DroneModel *droneModel() const;

    //! Return mission plan controller
    MissionPlanController *missionPlanController() const;

    //! Return flight controller
    FlightController *flightController() const;

    //! Return setting controller
    SettingController *settingController() const;

    //! Return battery controller
    BatteryController *batteryController() const;

    //! Return GPS controller
    GPSController *gpsController() const;

    //! Return drone by UID
    DroneBase *getDrone(const QString &sDroneUID) const;

private:
    //! Application title
    QString m_sApplicationTitle = "";

    //! Drone manager
    Model::DroneManager *m_pDroneManager = nullptr;

    //! Drone view model
    DroneModel *m_pDroneModel = nullptr;

    //! Drone list
    QVector<DroneBase *> m_vDrones;

    //! Current drone
    DroneBase *m_pCurrentDrone = nullptr;

    //! Mission plan controller
    MissionPlanController *m_pMissionPlanController = nullptr;

    //! Flight controller
    FlightController *m_pFlightController = nullptr;

    //! Setting controller
    SettingController *m_pSettingController = nullptr;

    //! Battery controller
    BatteryController *m_pBatteryController = nullptr;

    //! GPS controller
    GPSController *m_pGPSController = nullptr;

    //! Dialog mgr
    QQuickItem *m_pDialogMgr = nullptr;

public slots:
    //! New drone available
    void onNewDroneAvailable(const QString &sVideoUrl, const QGeoCoordinate &initialPosition, const QString &sDroneUID);

    //! Drone global status changed
    void onDroneGlobalStatusChanged();

signals:
    //! Start drone detection
    void startDroneDetection();

    //! Current drone changed
    void currentDroneChanged();

    //! Drone model view changed
    void droneModelChanged();

    //! Setting controller changed
    void settingControllerChanged();

    //! Mission plan controller changed
    void missionPlanControllerChanged();

    //! Flight controller changed
    void flightControllerChanged();

    //! Battery controller changed
    void batteryControllerChanged();

    //! GPS controller changed
    void gpsControllerChanged();

    //! Application title changed
    void applicationTitleChanged();
};

Q_DECLARE_METATYPE(MasterController::DroneError)

#endif // MASTERCONTROLLER_H

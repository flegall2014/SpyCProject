#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

// Qt
#include <QObject>

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

class MasterController : public QObject, public IService
{
    Q_OBJECT
    Q_PROPERTY(DroneModel *droneModel READ droneModel NOTIFY droneModelChanged)
    Q_PROPERTY(MissionPlanController *missionPlanController READ missionPlanController NOTIFY missionPlanControllerChanged)
    Q_PROPERTY(DroneBase *currentDrone READ currentDrone WRITE setCurrentDrone NOTIFY currentDroneChanged)
    Q_ENUMS(DroneError)

public:
    friend class MissionPlanController;

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

    //! Set drone state
    Q_INVOKABLE void setAllDroneState(const DroneBase::State &eState);

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Set current drone
    void setCurrentDrone(DroneBase *pDrone);

    //! Return current drone
    DroneBase *currentDrone() const;

private:
    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return drone model view
    DroneModel *droneModel() const;

    //! Return mission plan controller
    MissionPlanController *missionPlanController() const;

    //! Return drone by UID
    DroneBase *getDrone(const QString &sDroneUID) const;

private:
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

public slots:
    //! New drone available
    void onNewDroneAvailable(const QString &sVideoUrl, const QGeoCoordinate &initialPosition, const QString &sDroneUID);

    //! Position changed
    void onPositionChanged(const QGeoCoordinate &position, double dHeading, const QString &sDroneUID);

    //! Battery level changed
    void onBatteryLevelChanged(int iLevel, const QString &sDroneUID);

    //! GPS strength changed
    void onGPSStrengthChanged(int iStrength, const QString &sDroneUID);

    //! Mission plan changed
    void onMissionPlanChanged(const QString &sDroneUID);

    //! Safety changed
    void onSafetyChanged(const QString &sDroneUID);

signals:
    //! Current drone changed
    void currentDroneChanged();

    //! Drone model view changed
    void droneModelChanged();

    //! Mission plan controller changed
    void missionPlanControllerChanged();
};

#endif // MASTERCONTROLLER_H

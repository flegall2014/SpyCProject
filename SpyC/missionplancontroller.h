#ifndef MISSIONPLANCONTROLLER_H
#define MISSIONPLANCONTROLLER_H

// Qt
#include <QObject>
#include <QGeoCoordinate>
#include <QGeoPath>
#include <drone.h>

// Application
class MasterController;

class MissionPlanController : public QObject
{
    Q_OBJECT
    Q_ENUMS(SafetyError)
    Q_ENUMS(MissionPlanError)

public:
    enum MissionPlanError {EMPTY_SAFETY=Qt::UserRole+1, NOT_ENOUGH_POINTS_IN_SAFETY,
                           EMPTY_MISSION_PLAN, NOT_ENOUGH_POINTS_IN_MISSION_PLAN};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    MissionPlanController(QObject *pParent=nullptr);

    //! Destructor
    ~MissionPlanController();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Set master controller
    void setMasterController(MasterController *pMasterController);

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Validate mission plan
    Q_INVOKABLE void validateMissionPlan(const QString &sDroneUID);

    //! Validate safety
    Q_INVOKABLE void validateSafety(const QString &sDroneUID);

    //! Take off
    Q_INVOKABLE void takeOff(const QString &sDroneUID);

    //! Fail safe
    Q_INVOKABLE void failSafe(const QString &sDroneUID);

private:
    //! Master controller
    MasterController *m_pMasterController=nullptr;

public slots:
    //! Mission plan error
    void onMissionPlanError(const Model::Drone::DroneError &eError, const QString &sDroneUID);

    //! Fail safe done
    void onFailSafeDone(const QString &sDroneUID);

signals:
    //! Upload mission plan
    void uploadMissionPlan(const QGeoPath &geoPath, const QString &sDroneUID);

    //! Upload safety
    void uploadSafety(const QGeoPath &geoPath, const QString &sDroneUID);

    //! Send a take off request
    void takeOffRequest(const QString &sDroneUID);

    //! Send a failsafe request
    void failSafeRequest(const QString &sDroneUID);

    //! Mission plan error
    void missionPlanError(const MissionPlanError &eError, const QString &sDroneUID);
};

#endif // MISSIONPLANCONTROLLER_H

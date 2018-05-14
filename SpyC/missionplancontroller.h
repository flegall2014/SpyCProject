#ifndef MISSIONPLANCONTROLLER_H
#define MISSIONPLANCONTROLLER_H

// Qt
#include <QObject>
#include <QGeoCoordinate>
#include <QGeoPath>
class QQuickItem;

// Application
#include <drone.h>

// Application
#include <waypoint.h>
class MasterController;

class MissionPlanController : public QObject
{
    Q_OBJECT
    Q_ENUMS(MissionPlanError)

public:
    enum MissionPlanError {EMPTY_SAFETY=Qt::UserRole+1, NOT_ENOUGH_POINTS_IN_SAFETY,
                           EMPTY_MISSION_PLAN, NOT_ENOUGH_POINTS_IN_MISSION_PLAN, EMPTY_EXCLUSION_AREA,
                           EMPTY_LANDING_PLAN, UNEXPECTED_LANDING_PLAN_COUNT};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    MissionPlanController(QObject *pParent=nullptr);

    //! Destructor
    ~MissionPlanController();

    //-------------------------------------------------------------------------------------------------
    // IService interface
    //-------------------------------------------------------------------------------------------------

    //! Startup
    virtual bool startup(const QStringList &lArgs);

    //! Shutdown
    virtual void shutdown();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Set master controller
    void setMasterController(MasterController *pMasterController);

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Validate safety plan
    Q_INVOKABLE void validateSafetyPlanRequest(const QString &sDroneUID);

    //! Validate mission plan
    Q_INVOKABLE void validateMissionPlanRequest(const QString &sDroneUID);

    //! Validate landing plan
    Q_INVOKABLE void validateLandingPlanRequest(const QString &sDroneUID);

    //! Validate exclusion area
    Q_INVOKABLE void validateExclusionAreaRequest(const QString &sDroneUID);

private:
    //! Master controller
    MasterController *m_pMasterController=nullptr;

public slots:
    //! Validate mission plan
    void onValidateMissionPlan(const QString &sDroneUID);

    //! Validate safety
    void onValidateSafetyPlan(const QString &sDroneUID);

    //! Validate landing plan
    void onValidateLandingPlan(const QString &sDroneUID);

    //! Validate exclusion areas
    void onValidateExclusionAreas(const QString &sDroneUID);

    //! Mission plan changed
    void onMissionPlanChanged(const QString &sDroneUID);

    //! Safety changed
    void onSafetyChanged(const QString &sDroneUID);

    //! Landing plan changed
    void onLandingPlanChanged(const QString &sDroneUID);

    //! Exclusion area changed
    void onExclusionAreaChanged(const QString &sDroneUID);

    //! Mission plan error
    void onMissionPlanError(const Model::Drone::DroneError &eError, const QString &sDroneUID);

    //! Fail safe done
    void onFailSafeDone(const QString &sDroneUID);

signals:
    //! Validate safety request
    void validateSafetyPlanReq(const QString &sDroneUID);

    //! Validate mission plan request
    void validateMissionPlanReq(const QString &sDroneUID);

    //! Validate landing plan request
    void validateLandingPlanReq(const QString &sDroneUID);

    //! Validate exclusion area request
    void validateExclusionAreaReq(const QString &sDroneUID);

    //! Upload mission plan
    void uploadMissionPlan(const WayPointList &vWayPoints, const QString &sDroneUID);

    //! Upload safety
    void uploadSafety(const QGeoPath &geoPath, const QString &sDroneUID);

    //! Upload landing plan
    void uploadLandingPlan(const WayPointList &geoPath, const QString &sDroneUID);

    //! Upload exclusion areas
    void uploadExclusionArea(const QList<QGeoPath> &lExclusionArea, const QString &sDroneUID);

    //! Mission plan error
    void missionPlanError(const MissionPlanError &eError, const QString &sDroneUID);
};

Q_DECLARE_METATYPE(MissionPlanController::MissionPlanError)

#endif // MISSIONPLANCONTROLLER_H

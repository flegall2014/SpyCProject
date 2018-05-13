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
    Q_ENUMS(MissionPlanError)

public:
    enum MissionPlanError {EMPTY_SAFETY=Qt::UserRole+1, NOT_ENOUGH_POINTS_IN_SAFETY,
                           EMPTY_MISSION_PLAN, NOT_ENOUGH_POINTS_IN_MISSION_PLAN, EMPTY_EXCLUSION_AREA};

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

    //! Validate mission plan
    Q_INVOKABLE void validateMissionPlan(const QString &sDroneUID);

    //! Validate safety
    Q_INVOKABLE void validateSafety(const QString &sDroneUID);

    //! Validate exclusion areas
    Q_INVOKABLE void validateExclusionAreas(const QString &sDroneUID);

private:
    //! Master controller
    MasterController *m_pMasterController=nullptr;

public slots:
    //! Mission plan changed
    void onMissionPlanChanged(const QString &sDroneUID);

    //! Safety changed
    void onSafetyChanged(const QString &sDroneUID);

    //! Exclusion area changed
    void onExclusionAreaChanged(const QString &sDroneUID);

    //! Mission plan error
    void onMissionPlanError(const Model::Drone::DroneError &eError, const QString &sDroneUID);

    //! Fail safe done
    void onFailSafeDone(const QString &sDroneUID);

signals:
    //! Upload mission plan
    void uploadMissionPlan(const QGeoPath &geoPath, const QString &sDroneUID);

    //! Upload safety
    void uploadSafety(const QGeoPath &geoPath, const QString &sDroneUID);

    //! Upload exclusion areas
    void uploadExclusionArea(const QList<QGeoPath> &lExclusionArea, const QString &sDroneUID);

    //! Mission plan error
    void missionPlanError(const MissionPlanError &eError, const QString &sDroneUID);
};

Q_DECLARE_METATYPE(MissionPlanController::MissionPlanError)

#endif // MISSIONPLANCONTROLLER_H

// Qt
#include <QDebug>

// Application
#include "missionplancontroller.h"
#include "mastercontroller.h"
#include "dronebase.h"
#include "waypointmodel.h"
#include "exclusionareamodel.h"

//-------------------------------------------------------------------------------------------------

MissionPlanController::MissionPlanController(QObject *pParent) : QObject(pParent)
{
    connect(this, &MissionPlanController::validateMissionPlanReq, this, &MissionPlanController::onValidateMissionPlan, Qt::QueuedConnection);
    connect(this, &MissionPlanController::validateSafetyPlanReq, this, &MissionPlanController::onValidateSafetyPlan, Qt::QueuedConnection);
    connect(this, &MissionPlanController::validateLandingPlanReq, this, &MissionPlanController::onValidateLandingPlan, Qt::QueuedConnection);
    connect(this, &MissionPlanController::validateExclusionAreaReq, this, &MissionPlanController::onValidateExclusionAreas, Qt::QueuedConnection);
}

//-------------------------------------------------------------------------------------------------

MissionPlanController::~MissionPlanController()
{

}

//-------------------------------------------------------------------------------------------------

bool MissionPlanController::startup(const QStringList &lArgs)
{
    Q_UNUSED(lArgs);
    return true;
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::shutdown()
{

}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::setMasterController(MasterController *pMasterController)
{
    m_pMasterController = pMasterController;
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::validateMissionPlanRequest(const QString &sDroneUID)
{
    emit validateMissionPlanReq(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onValidateMissionPlan(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
        {
            // Retrieve safety area
            QGeoPath missionPlan = pDrone->missionPlanModel()->path();
            if (!missionPlan.isEmpty())
            {
                if (missionPlan.size() > 2)
                    emit uploadMissionPlan(pDrone->missionPlanModel()->wayPoints(), pDrone->uid());
                else
                    emit missionPlanError(MissionPlanError::NOT_ENOUGH_POINTS_IN_MISSION_PLAN, pDrone->uid());
            }
            else emit missionPlanError(MissionPlanError::EMPTY_MISSION_PLAN, pDrone->uid());
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::validateSafetyPlanRequest(const QString &sDroneUID)
{
    emit validateSafetyPlanReq(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onValidateSafetyPlan(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
        {
            // Retrieve safety area
            QGeoPath safety = pDrone->safetyModel()->path();
            if (!safety.isEmpty())
            {
                if (safety.size() > 2)
                {
                    pDrone->closeSafety();
                    emit uploadSafety(pDrone->safetyModel()->path(), pDrone->uid());
                }
                else
                    emit missionPlanError(MissionPlanError::NOT_ENOUGH_POINTS_IN_SAFETY, pDrone->uid());
            }
            else emit missionPlanError(MissionPlanError::EMPTY_SAFETY, pDrone->uid());
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::validateLandingPlanRequest(const QString &sDroneUID)
{
    emit validateLandingPlanReq(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onValidateLandingPlan(const QString &sDroneUID)
{
    qDebug() << "onValidateLandingPlan";
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
        {
            // Retrieve landing plan
            QGeoPath landingPlan = pDrone->landingPlanModel()->path();
            if (!landingPlan.isEmpty())
            {
                if (landingPlan.size() == 3)
                {
                    qDebug() << "UPLOADING LANDING PLAN";
                    emit uploadLandingPlan(pDrone->landingPlanModel()->wayPoints(), pDrone->uid());
                }
                else
                {
                    emit missionPlanError(MissionPlanError::UNEXPECTED_LANDING_PLAN_COUNT, pDrone->uid());
                }
            }
            else emit missionPlanError(MissionPlanError::EMPTY_LANDING_PLAN, pDrone->uid());
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::validateExclusionAreaRequest(const QString &sDroneUID)
{
    emit validateExclusionAreaReq(sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onValidateExclusionAreas(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
        {
            // Retrieve exclusion areas
            QList<QGeoPath> lGeoPathList = pDrone->exclusionAreaModel()->getExclusionAreaList();
            if (!lGeoPathList.isEmpty())
                emit uploadExclusionArea(lGeoPathList, pDrone->uid());
            else
                emit missionPlanError(MissionPlanError::EMPTY_EXCLUSION_AREA, pDrone->uid());
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onMissionPlanChanged(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            pDrone->setState(DroneBase::IDLE);
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onSafetyChanged(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
        {
            pDrone->setState(DroneBase::IDLE);
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onLandingPlanChanged(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
        {
            pDrone->setState(DroneBase::IDLE);
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onExclusionAreaChanged(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
        {
            pDrone->setState(DroneBase::IDLE);
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onMissionPlanError(const Model::Drone::DroneError &eError, const QString &sDroneUID)
{
    qDebug() << "*** MISSION PLAN ERROR ***";
    if (eError == Model::Drone::NO_SAFETY)
        emit missionPlanError(EMPTY_SAFETY, sDroneUID);
    else
    if (eError == Model::Drone::NO_LANDING_PLAN)
        emit missionPlanError(EMPTY_LANDING_PLAN, sDroneUID);
    else
    if (eError == Model::Drone::NO_MISSION_PLAN)
        emit missionPlanError(EMPTY_MISSION_PLAN, sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onFailSafeDone(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            pDrone->setState(DroneBase::IDLE);
    }
}

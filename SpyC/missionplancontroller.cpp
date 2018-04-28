// Qt
#include <QDebug>

// Application
#include "missionplancontroller.h"
#include "mastercontroller.h"
#include "dronebase.h"
#include "waypointmodel.h"

//-------------------------------------------------------------------------------------------------

MissionPlanController::MissionPlanController(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

MissionPlanController::~MissionPlanController()
{

}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::setMasterController(MasterController *pMasterController)
{
    m_pMasterController = pMasterController;
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::validateMissionPlan(const QString &sDroneUID)
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
                    QGeoPath missionPlan = pDrone->missionPlanModel()->path();
                    if (missionPlan.size() > 2)
                        emit uploadMissionPlan(pDrone->missionPlanModel()->path(), pDrone->uid());
                    else
                        emit missionPlanError(MissionPlanError::NOT_ENOUGH_POINTS_IN_MISSION_PLAN, pDrone->uid());
                }
                else emit missionPlanError(MissionPlanError::NOT_ENOUGH_POINTS_IN_SAFETY, pDrone->uid());
            }
            else emit missionPlanError(MissionPlanError::EMPTY_SAFETY, pDrone->uid());
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::validateSafety(const QString &sDroneUID)
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
                    emit uploadSafety(pDrone->safetyModel()->path(), pDrone->uid());
                else
                    emit missionPlanError(MissionPlanError::NOT_ENOUGH_POINTS_IN_SAFETY, pDrone->uid());
            }
            else emit missionPlanError(MissionPlanError::EMPTY_SAFETY, pDrone->uid());
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::takeOff(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            emit startTakeOff(pDrone->uid());
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::failSafe(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            emit startFailSafe(pDrone->uid());
    }
}

//-------------------------------------------------------------------------------------------------

void MissionPlanController::onMissionPlanError(const Model::Drone::DroneError &eError, const QString &sDroneUID)
{
    if (eError == Model::Drone::NO_SAFETY)
        emit missionPlanError(EMPTY_SAFETY, sDroneUID);
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

// Qt
#include <QDebug>

// Application
#include "mastercontroller.h"
#include "pluginloader.h"
#include "droneview.h"
#include "missionplancontroller.h"
#include "dronebase.h"
#include <dronemanager.h>

//-------------------------------------------------------------------------------------------------

MasterController::MasterController(QObject *pParent) : QObject(pParent)
{
    m_pDroneView = new DroneView(this);
    m_pMissionPlanController = new MissionPlanController(this);
    m_pMissionPlanController->setMasterController(this);
}

//-------------------------------------------------------------------------------------------------

MasterController::~MasterController()
{

}

//-------------------------------------------------------------------------------------------------

bool MasterController::startup(const QStringList &lArgs)
{
    return true;
}

//-------------------------------------------------------------------------------------------------

void MasterController::shutdown()
{

}

//-------------------------------------------------------------------------------------------------

void MasterController::setModel(Model::DroneManager *pDroneManager)
{
    m_pDroneManager = pDroneManager;
    if (m_pDroneManager != nullptr)
    {
        // From model to view
        connect(m_pDroneManager, &Model::DroneManager::newDroneAvailable, this, &MasterController::onNewDroneAvailable);
        connect(m_pDroneManager, &Model::DroneManager::positionChanged, this, &MasterController::onPositionChanged);
        connect(m_pDroneManager, &Model::DroneManager::batteryLevelChanged, this, &MasterController::onBatteryLevelChanged);
        connect(m_pDroneManager, &Model::DroneManager::gpsStrengthChanged, this, &MasterController::onGPSStrengthChanged);
        connect(m_pDroneManager, &Model::DroneManager::missionPlanChanged, this, &MasterController::onMissionPlanChanged);
        connect(m_pDroneManager, &Model::DroneManager::safetyChanged, this, &MasterController::onSafetyChanged);
        connect(m_pDroneManager, &Model::DroneManager::droneError, m_pMissionPlanController, &MissionPlanController::onMissionPlanError);
        connect(m_pDroneManager, &Model::DroneManager::failSafeDone, m_pMissionPlanController, &MissionPlanController::onFailSafeDone);

        // From view to model
        connect(m_pMissionPlanController, &MissionPlanController::uploadMissionPlan, m_pDroneManager, &Model::DroneManager::onUploadMissionPlan);
        connect(m_pMissionPlanController, &MissionPlanController::uploadSafety, m_pDroneManager, &Model::DroneManager::onUploadSafety);
        connect(m_pMissionPlanController, &MissionPlanController::startTakeOff, m_pDroneManager, &Model::DroneManager::onTakeOff);
        connect(m_pMissionPlanController, &MissionPlanController::startFailSafe, m_pDroneManager, &Model::DroneManager::onFailSafe);
    }
}

//-------------------------------------------------------------------------------------------------

void MasterController::setAllDroneState(const DroneBase::State &eState)
{
    foreach (DroneBase *pDrone, m_vDrones)
        if (pDrone != nullptr)
            pDrone->setState(eState);
}

//-------------------------------------------------------------------------------------------------

DroneView *MasterController::droneView() const
{
    return m_pDroneView;
}

//-------------------------------------------------------------------------------------------------

MissionPlanController *MasterController::missionPlanController() const
{
    return m_pMissionPlanController;
}

//-------------------------------------------------------------------------------------------------

DroneBase *MasterController::getDrone(const QString &sDroneUID) const
{
    foreach (DroneBase *pDrone, m_vDrones)
        if ((pDrone != nullptr) && (pDrone->uid() == sDroneUID))
            return pDrone;
    return nullptr;
}

//-------------------------------------------------------------------------------------------------

void MasterController::onNewDroneAvailable(const QString &sVideoUrl, const QGeoCoordinate &initialPosition, const QString &sDroneUID)
{
    DroneBase *pDrone = new DroneBase(sDroneUID, sVideoUrl, initialPosition, this);
    m_vDrones << pDrone;
    m_pDroneView->addDrone(pDrone);
}

//-------------------------------------------------------------------------------------------------

void MasterController::onBatteryLevelChanged(int iLevel, const QString &sDroneUID)
{
    DroneBase *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
        pDrone->setBatteryLevel(iLevel);
}

//-------------------------------------------------------------------------------------------------

void MasterController::onGPSStrengthChanged(int iStrength, const QString &sDroneUID)
{
    DroneBase *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
        pDrone->setGPSStrength(iStrength);
}

//-------------------------------------------------------------------------------------------------

void MasterController::onPositionChanged(const QGeoCoordinate &position, double dHeading, const QString &sDroneUID)
{
    DroneBase *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        if (pDrone->state() != DroneBase::FLYING)
            pDrone->setState(DroneBase::FLYING);
        pDrone->setPosition(position);
        pDrone->setHeading(dHeading);
    }
}

//-------------------------------------------------------------------------------------------------

void MasterController::onMissionPlanChanged(const QString &sDroneUID)
{
    DroneBase *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
        pDrone->setState(DroneBase::IDLE);
}

//-------------------------------------------------------------------------------------------------

void MasterController::onSafetyChanged(const QString &sDroneUID)
{
    DroneBase *pDrone = getDrone(sDroneUID);
    if (pDrone != nullptr)
    {
        pDrone->setState(DroneBase::IDLE);
    }
}

//-------------------------------------------------------------------------------------------------

void MasterController::setCurrentDrone(DroneBase *pDrone)
{
    m_pCurrentDrone = pDrone;
    emit currentDroneChanged();
}

//-------------------------------------------------------------------------------------------------

DroneBase *MasterController::currentDrone() const
{
    return m_pCurrentDrone;
}

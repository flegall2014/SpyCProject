// Qt
#include <QDebug>
#include <QTextToSpeech>

// Application
#include "mastercontroller.h"
#include "pluginloader.h"
#include "dronemodel.h"
#include "settingcontroller.h"
#include "missionplancontroller.h"
#include "flightcontroller.h"
#include "batterycontroller.h"
#include "gpscontroller.h"
#include "dronebase.h"
#include <dronemanager.h>

//-------------------------------------------------------------------------------------------------

MasterController::MasterController(QObject *pParent) : QObject(pParent)
{
    // Application main title
    m_sApplicationTitle = tr("Welcome to Spy'C ground station");

    // Main drone model
    m_pDroneModel = new DroneModel(this);

    // Setup mission plan controller
    m_pMissionPlanController = new MissionPlanController(this);
    m_pMissionPlanController->setMasterController(this);

    // Setup flight controller
    m_pFlightController = new FlightController(this);
    m_pFlightController->setMasterController(this);

    // Setup setting controller
    m_pSettingController = new SettingController(this);
    m_pSettingController->setMasterController(this);

    // Setup battery controller
    m_pBatteryController = new BatteryController(this);
    m_pBatteryController->setMasterController(this);

    // Setup gps controller
    m_pGPSController = new GPSController(this);
    m_pGPSController->setMasterController(this);
}

//-------------------------------------------------------------------------------------------------

MasterController::~MasterController()
{

}

//-------------------------------------------------------------------------------------------------

bool MasterController::startup(const QStringList &lArgs)
{
    if (!m_pSettingController->startup(lArgs))
        return false;
    if (!m_pMissionPlanController->startup(lArgs))
        return false;
    if (!m_pFlightController->startup(lArgs))
        return false;
    if (!m_pBatteryController->startup(lArgs))
        return false;
    if (!m_pGPSController->startup(lArgs))
        return false;
    return true;
}

//-------------------------------------------------------------------------------------------------

void MasterController::shutdown()
{
    m_pMissionPlanController->shutdown();
    m_pFlightController->shutdown();
    m_pSettingController->shutdown();
    m_pBatteryController->shutdown();
    m_pGPSController->shutdown();
}

//-------------------------------------------------------------------------------------------------

void MasterController::setModel(Model::DroneManager *pDroneManager)
{
    m_pDroneManager = pDroneManager;
    if (m_pDroneManager != nullptr)
    {
        // From model to view
        connect(m_pDroneManager, &Model::DroneManager::newDroneAvailable, this, &MasterController::onNewDroneAvailable, Qt::QueuedConnection);
        connect(m_pDroneManager, &Model::DroneManager::positionChanged, m_pFlightController, &FlightController::onPositionChanged, Qt::QueuedConnection);
        connect(m_pDroneManager, &Model::DroneManager::batteryLevelChanged, m_pBatteryController, &BatteryController::onBatteryLevelChanged, Qt::QueuedConnection);
        connect(m_pDroneManager, &Model::DroneManager::gpsStrengthChanged, m_pGPSController, &GPSController::onGPSStrengthChanged, Qt::QueuedConnection);
        connect(m_pDroneManager, &Model::DroneManager::missionPlanChanged, m_pMissionPlanController, &MissionPlanController::onMissionPlanChanged, Qt::QueuedConnection);
        connect(m_pDroneManager, &Model::DroneManager::safetyChanged, m_pMissionPlanController, &MissionPlanController::onSafetyChanged, Qt::QueuedConnection);
        connect(m_pDroneManager, &Model::DroneManager::landingPlanChanged, m_pMissionPlanController, &MissionPlanController::onLandingPlanChanged, Qt::QueuedConnection);
        connect(m_pDroneManager, &Model::DroneManager::exclusionAreaChanged, m_pMissionPlanController, &MissionPlanController::onExclusionAreaChanged, Qt::QueuedConnection);
        connect(m_pDroneManager, &Model::DroneManager::droneError, m_pMissionPlanController, &MissionPlanController::onMissionPlanError, Qt::QueuedConnection);
        connect(m_pDroneManager, &Model::DroneManager::failSafeDone, m_pMissionPlanController, &MissionPlanController::onFailSafeDone, Qt::QueuedConnection);

        // From view to model
        connect(this, &MasterController::startDroneDetection, m_pDroneManager, &Model::DroneManager::onStartDroneDetection, Qt::QueuedConnection);
        connect(m_pMissionPlanController, &MissionPlanController::uploadMissionPlan, m_pDroneManager, &Model::DroneManager::onUploadMissionPlan, Qt::QueuedConnection);
        connect(m_pMissionPlanController, &MissionPlanController::uploadSafety, m_pDroneManager, &Model::DroneManager::onUploadSafety, Qt::QueuedConnection);
        connect(m_pMissionPlanController, &MissionPlanController::uploadLandingPlan, m_pDroneManager, &Model::DroneManager::onUploadLandingPlan, Qt::QueuedConnection);
        connect(m_pMissionPlanController, &MissionPlanController::uploadExclusionArea, m_pDroneManager, &Model::DroneManager::onUploadExclusionArea, Qt::QueuedConnection);
        connect(m_pFlightController, &FlightController::takeOffRequest, m_pDroneManager, &Model::DroneManager::onTakeOffRequest, Qt::QueuedConnection);
        connect(m_pFlightController, &FlightController::failSafeRequest, m_pDroneManager, &Model::DroneManager::onFailSafeRequest, Qt::QueuedConnection);
    }
}

//-------------------------------------------------------------------------------------------------

void MasterController::detectDrones()
{
    emit startDroneDetection();
}

//-------------------------------------------------------------------------------------------------

void MasterController::updateApplicationTitle(const QString &sArmy, const QString &sUnit, const QString &sMission, const QString &sOperator)
{
    QString sApplicationTitle = QString("[%1] [%2] [%3] [%4]").arg(sArmy).arg(sUnit).arg(sMission).arg(sOperator);
    setApplicationTitle(sApplicationTitle);
}

//-------------------------------------------------------------------------------------------------

DroneModel *MasterController::droneModel() const
{
    return m_pDroneModel;
}

//-------------------------------------------------------------------------------------------------

MissionPlanController *MasterController::missionPlanController() const
{
    return m_pMissionPlanController;
}

//-------------------------------------------------------------------------------------------------

FlightController *MasterController::flightController() const
{
    return m_pFlightController;
}

//-------------------------------------------------------------------------------------------------

SettingController *MasterController::settingController() const
{
    return m_pSettingController;
}

//-------------------------------------------------------------------------------------------------

BatteryController *MasterController::batteryController() const
{
    return m_pBatteryController;
}

//-------------------------------------------------------------------------------------------------

GPSController *MasterController::gpsController() const
{
    return m_pGPSController;
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
    pDrone->initialize(m_pSettingController->allSettings());
    connect(pDrone, &DroneBase::globalStatusChanged, this, &MasterController::onDroneGlobalStatusChanged, Qt::QueuedConnection);
    m_vDrones << pDrone;
    m_pDroneModel->addDrone(pDrone);
}

//-------------------------------------------------------------------------------------------------

void MasterController::onDroneGlobalStatusChanged()
{
    DroneBase *pSender = dynamic_cast<DroneBase *>(sender());
    if (pSender != nullptr)
    {
        if (pSender->globalStatus() != DroneBase::NOMINAL)
        {
            QString sVoiceMsg = "";
            if (pSender->globalStatus() == DroneBase::WARNING)
            {
                sVoiceMsg = QString("%1 is in warning state").arg(pSender->uid());
            }
            else
            if (pSender->globalStatus() == DroneBase::CRITICAL)
            {
                sVoiceMsg = QString("%1 is in critical state").arg(pSender->uid());
            }
            if (!sVoiceMsg.isEmpty())
                m_pSettingController->say(sVoiceMsg);
        }
    }
}

//-------------------------------------------------------------------------------------------------

void MasterController::setCurrentDrone(DroneBase *pCurrentDrone)
{
    m_pCurrentDrone = pCurrentDrone;
    emit currentDroneChanged();
}

//-------------------------------------------------------------------------------------------------

DroneBase *MasterController::currentDrone() const
{
    return m_pCurrentDrone;
}

//-------------------------------------------------------------------------------------------------

void MasterController::setApplicationTitle(const QString &sApplicationTitle)
{
    m_sApplicationTitle = sApplicationTitle;
    emit applicationTitleChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &MasterController::applicationTitle() const
{
    return m_sApplicationTitle;
}



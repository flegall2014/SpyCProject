// Qt
#include <QDebug>

// Application
#include "flightcontroller.h"
#include "mastercontroller.h"

//-------------------------------------------------------------------------------------------------

FlightController::FlightController(QObject *parent) : QObject(parent)
{

}

//-------------------------------------------------------------------------------------------------

FlightController::~FlightController()
{

}

//-------------------------------------------------------------------------------------------------

bool FlightController::startup(const QStringList &lArgs)
{
    Q_UNUSED(lArgs);
    return true;
}

//-------------------------------------------------------------------------------------------------

void FlightController::shutdown()
{

}

//-------------------------------------------------------------------------------------------------

void FlightController::setMasterController(MasterController *pMasterController)
{
    m_pMasterController = pMasterController;
}

//-------------------------------------------------------------------------------------------------

void FlightController::takeOff(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            emit takeOffRequest(pDrone->uid());
    }
}

//-------------------------------------------------------------------------------------------------

void FlightController::failSafe(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            emit failSafeRequest(pDrone->uid());
    }
}

//-------------------------------------------------------------------------------------------------

void FlightController::onFailSafeDone(const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            pDrone->setState(DroneBase::IDLE);
    }
}

//-------------------------------------------------------------------------------------------------

void FlightController::onBatteryLevelChanged(int iLevel, const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            pDrone->setBatteryLevel(iLevel);
    }
}

//-------------------------------------------------------------------------------------------------

void FlightController::onGPSStrengthChanged(int iStrength, const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            pDrone->setGPSStrength(iStrength);
    }
}

//-------------------------------------------------------------------------------------------------

void FlightController::onPositionChanged(const QGeoCoordinate &position, double dHeading, const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
        {
            if (pDrone->state() != DroneBase::FLYING)
                pDrone->setState(DroneBase::FLYING);
            pDrone->setPosition(position);
            pDrone->setHeading(dHeading);
        }
    }
}

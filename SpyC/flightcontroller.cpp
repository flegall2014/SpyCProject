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


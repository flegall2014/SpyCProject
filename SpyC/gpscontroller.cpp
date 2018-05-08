// Qt
#include <QDebug>

// Application
#include "gpscontroller.h"
#include "mastercontroller.h"

//-------------------------------------------------------------------------------------------------

GPSController::GPSController(QObject *parent) : QObject(parent)
{

}

//-------------------------------------------------------------------------------------------------

GPSController::~GPSController()
{

}

//-------------------------------------------------------------------------------------------------

bool GPSController::startup(const QStringList &lArgs)
{
    Q_UNUSED(lArgs);
    return true;
}

//-------------------------------------------------------------------------------------------------

void GPSController::shutdown()
{

}

//-------------------------------------------------------------------------------------------------

void GPSController::setMasterController(MasterController *pMasterController)
{
    m_pMasterController = pMasterController;
}

//-------------------------------------------------------------------------------------------------

void GPSController::onGPSStrengthChanged(int iGPSStrength, const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            pDrone->setGPSStrength(iGPSStrength);
    }
}

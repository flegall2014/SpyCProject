// Qt
#include <QDebug>

// Application
#include "batterycontroller.h"
#include "mastercontroller.h"

//-------------------------------------------------------------------------------------------------

BatteryController::BatteryController(QObject *parent) : QObject(parent)
{

}

//-------------------------------------------------------------------------------------------------

BatteryController::~BatteryController()
{

}

//-------------------------------------------------------------------------------------------------

bool BatteryController::startup(const QStringList &lArgs)
{
    Q_UNUSED(lArgs);
    return true;
}

//-------------------------------------------------------------------------------------------------

void BatteryController::shutdown()
{

}

//-------------------------------------------------------------------------------------------------

void BatteryController::setMasterController(MasterController *pMasterController)
{
    m_pMasterController = pMasterController;
}

//-------------------------------------------------------------------------------------------------

void BatteryController::onBatteryLevelChanged(int iLevel, const QString &sDroneUID)
{
    if (m_pMasterController != nullptr)
    {
        DroneBase *pDrone = m_pMasterController->getDrone(sDroneUID);
        if (pDrone != nullptr)
            pDrone->setBatteryLevel(iLevel);
    }
}

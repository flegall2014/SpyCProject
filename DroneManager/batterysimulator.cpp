// Qt
#include <QDebug>

// Application
#include "batterysimulator.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

BatterySimulator::BatterySimulator(const QString &sDroneUID, QObject *pParent) : BaseSimulator(sDroneUID, pParent)
{
    m_timer.setInterval(500);
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &BatterySimulator::onTimeOut);
}

//-------------------------------------------------------------------------------------------------

BatterySimulator::~BatterySimulator()
{

}

//-------------------------------------------------------------------------------------------------

void BatterySimulator::start()
{
    m_timer.start();
}

//-------------------------------------------------------------------------------------------------

void BatterySimulator::onTimeOut()
{
    emit batteryLevelChanged(m_iBatteryLevel, m_sDroneUID);
    m_iBatteryLevel--;
    if (m_iBatteryLevel < 0)
        m_iBatteryLevel = 100;
    m_timer.start();
}

//-------------------------------------------------------------------------------------------------

void BatterySimulator::stop()
{
    m_iBatteryLevel = 0;
    m_timer.stop();
}

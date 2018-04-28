// Qt
#include <QDebug>

// Application
#include "gpssimulator.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

GPSSimulator::GPSSimulator(const QString &sDroneUID, QObject *pParent) : BaseSimulator(sDroneUID, pParent)
{
    m_timer.setInterval(1000);
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &GPSSimulator::onTimeOut);
    m_timer.start();
}

//-------------------------------------------------------------------------------------------------

GPSSimulator::~GPSSimulator()
{

}

//-------------------------------------------------------------------------------------------------

void GPSSimulator::start()
{
    m_bRepeat = true;
    m_timer.start();
}

//-------------------------------------------------------------------------------------------------

void GPSSimulator::onTimeOut()
{
    m_iGPSStrength++;
    emit gpsStrengthChanged(m_iGPSStrength%100, m_sDroneUID);
    if (m_bRepeat)
        m_timer.start();
}

//-------------------------------------------------------------------------------------------------

void GPSSimulator::stop()
{
    m_iGPSStrength = 0;
    m_timer.stop();
}

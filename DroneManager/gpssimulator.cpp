// Qt
#include <QDebug>

// Application
#include "gpssimulator.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

GPSSimulator::GPSSimulator(const QString &sDroneUID, QObject *pParent) : BaseSimulator(sDroneUID, pParent)
{
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &GPSSimulator::onTimeOut, Qt::QueuedConnection);
    m_timer.start(0);
}

//-------------------------------------------------------------------------------------------------

GPSSimulator::~GPSSimulator()
{

}

//-------------------------------------------------------------------------------------------------

void GPSSimulator::start()
{
    m_timer.setInterval(1000);
    m_bRepeat = true;
    m_timer.start();
}

//-------------------------------------------------------------------------------------------------

void GPSSimulator::onTimeOut()
{
    emit gpsStrengthChanged(m_iGPSStrength, m_sDroneUID);
    m_iGPSStrength--;
    if (m_iGPSStrength < 0)
        m_iGPSStrength = 100;
    if (m_bRepeat)
        m_timer.start();
}

//-------------------------------------------------------------------------------------------------

void GPSSimulator::stop()
{
    m_timer.stop();
}

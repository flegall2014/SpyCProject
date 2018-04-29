// Qt
#include <QDebug>

// Application
#include "flightsimulator.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

FlightSimulator::FlightSimulator(const QString &sDroneUID, QObject *pParent) : BaseSimulator(sDroneUID, pParent)
{
    m_timer.setInterval(100);
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &FlightSimulator::onTimeOut, Qt::QueuedConnection);
}

//-------------------------------------------------------------------------------------------------

FlightSimulator::~FlightSimulator()
{

}

//-------------------------------------------------------------------------------------------------

void FlightSimulator::computeFlightPath(const QGeoPath &geoPath, int iPointCount)
{
    m_iPointIndex++;
    m_vDetailedPath.clear();
    m_vHeading.clear();
    int iPathSize = geoPath.size();
    for (int i=0; i<iPathSize-1; i++)
    {
        QGeoCoordinate firstCoord = geoPath.coordinateAt(i);
        QGeoCoordinate secondCoord = geoPath.coordinateAt(i+1);
        double m = (secondCoord.longitude()-firstCoord.longitude())/(secondCoord.latitude()-firstCoord.latitude());
        double p = firstCoord.longitude()-m*firstCoord.latitude();
        double dStep = (secondCoord.latitude()-firstCoord.latitude())/iPointCount;
        double dHeading = atan2(firstCoord.longitude() - secondCoord.longitude(), firstCoord.latitude() - secondCoord.latitude());

        for (int j=0; j<iPointCount; j++)
        {
            double dLatitude = geoPath.coordinateAt(i).latitude()+j*dStep;
            double dLongitude = m*dLatitude+p;
            m_vDetailedPath << QGeoCoordinate(dLatitude, dLongitude);
            m_vHeading << dHeading*180/M_PI+180;
        }
    }
}

//-------------------------------------------------------------------------------------------------

void FlightSimulator::start()
{
    m_iPointIndex = 0;
    m_timer.start();
}

//-------------------------------------------------------------------------------------------------

void FlightSimulator::onTimeOut()
{
    int iActualIndex = m_iPointIndex%m_vDetailedPath.size();
    emit positionChanged(m_vDetailedPath[iActualIndex], m_vHeading[iActualIndex], m_sDroneUID);
    m_iPointIndex++;
    m_timer.start();
}

//-------------------------------------------------------------------------------------------------

void FlightSimulator::stop()
{
    m_timer.stop();
}

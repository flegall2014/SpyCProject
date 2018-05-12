// Qt
#include <QDebug>

// Application
#include "drone.h"
#include "flightsimulator.h"
#include "batterysimulator.h"
#include "gpssimulator.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

Drone::Drone(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initalPosition, QObject *pParent) : QObject(pParent),
    m_sDroneUID(sDroneUID), m_sVideoUrl(sVideoUrl), m_initialPosition(initalPosition)
{
    // Register type
    qRegisterMetaType<Drone::DroneError>("Drone::DroneError");

    // Flight simulator
    m_pFlightSimulator = new FlightSimulator(sDroneUID, this);
    connect(m_pFlightSimulator, &FlightSimulator::positionChanged, this, &Drone::positionChanged, Qt::QueuedConnection);

    // Battery simulator
    m_pBatterySimulator = new BatterySimulator(sDroneUID, this);
    connect(m_pBatterySimulator, &BatterySimulator::batteryLevelChanged, this, &Drone::batteryLevelChanged, Qt::QueuedConnection);

    // GPS simulator
    m_pGPSSimulator = new GPSSimulator(sDroneUID, this);
    connect(m_pGPSSimulator, &GPSSimulator::gpsStrengthChanged, this, &Drone::gpsStrengthChanged, Qt::QueuedConnection);
}

//-------------------------------------------------------------------------------------------------

Drone::~Drone()
{

}

//-------------------------------------------------------------------------------------------------

const QString &Drone::uid() const
{
    return m_sDroneUID;
}

//-------------------------------------------------------------------------------------------------

const QString &Drone::videoUrl() const
{
    return m_sVideoUrl;
}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &Drone::initialPosition() const
{
    return m_initialPosition;
}

//-------------------------------------------------------------------------------------------------

void Drone::setSafety(const QGeoPath &geoPath)
{
    m_safety = geoPath;
    emit safetyChanged(m_sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void Drone::setMissionPlan(const QGeoPath &geoPath)
{
    m_missionPlan = geoPath;
    emit missionPlanChanged(m_sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void Drone::setExclusionArea(const QList<QGeoPath> &lExclusionArea)
{
    m_lExclusionArea = lExclusionArea;
    emit exclusionAreaChanged(m_sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void Drone::takeOff()
{
    if (m_safety.isEmpty())
        emit droneError(NO_SAFETY, m_sDroneUID);
    else
    if (m_missionPlan.isEmpty())
        emit droneError(NO_MISSION_PLAN, m_sDroneUID);
    else
    {
        m_pFlightSimulator->computeFlightPath(m_missionPlan);
        m_pFlightSimulator->start();
        m_pBatterySimulator->start();
        m_pGPSSimulator->start();
    }
}

//-------------------------------------------------------------------------------------------------

void Drone::failSafe()
{
    m_pFlightSimulator->stop();
    m_pBatterySimulator->stop();
    m_pGPSSimulator->stop();
    emit failSafeDone(m_sDroneUID);
}

//-------------------------------------------------------------------------------------------------

void Drone::onPositionChanged(const QGeoCoordinate &geoCoord, double dHeading)
{
    emit positionChanged(geoCoord, dHeading, m_sDroneUID);
}

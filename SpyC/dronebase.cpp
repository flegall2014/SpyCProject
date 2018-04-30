// Qt
#include <QDebug>

// Application
#include "dronebase.h"
#include <drone.h>
#include "waypointmodel.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

DroneBase::DroneBase(QObject *parent) : QObject(parent)
{
    // Mission plan model
    m_pMissionPlanModel = new WayPointModel(this);
    m_pSafetyModel = new WayPointModel(this);
    connect(this, &DroneBase::batteryStatusChanged, this, &DroneBase::globalStatusChanged, Qt::QueuedConnection);
    connect(this, &DroneBase::gpsStrengthChanged, this, &DroneBase::globalStatusChanged, Qt::QueuedConnection);
    connect(this, &DroneBase::positionStatusChanged, this, &DroneBase::globalStatusChanged, Qt::QueuedConnection);
}

//-------------------------------------------------------------------------------------------------

DroneBase::DroneBase(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPosition, QObject *parent) :
    QObject(parent), m_sDroneUID(sDroneUID), m_sVideoUrl(sVideoUrl), m_initialPosition(initialPosition), m_position(initialPosition)
{
    // Mission plan model
    m_pMissionPlanModel = new WayPointModel(this);
    m_pSafetyModel = new WayPointModel(this);
    connect(this, &DroneBase::batteryStatusChanged, this, &DroneBase::globalStatusChanged, Qt::QueuedConnection);
    connect(this, &DroneBase::gpsStrengthChanged, this, &DroneBase::globalStatusChanged, Qt::QueuedConnection);
    connect(this, &DroneBase::positionStatusChanged, this, &DroneBase::globalStatusChanged, Qt::QueuedConnection);
}

//-------------------------------------------------------------------------------------------------

DroneBase::~DroneBase()
{

}

//-------------------------------------------------------------------------------------------------

const QString &DroneBase::uid() const
{
    return m_sDroneUID;
}

//-------------------------------------------------------------------------------------------------

const QString &DroneBase::videoUrl() const
{
    return m_sVideoUrl;
}

//-------------------------------------------------------------------------------------------------

int DroneBase::batteryLevel() const
{
    return m_iBatteryLevel;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setBatteryLevel(int iBatteryLevel)
{
    m_iBatteryLevel = iBatteryLevel;
    emit batteryLevelChanged();
    emit batteryStatusChanged();
}

//-------------------------------------------------------------------------------------------------

int DroneBase::gpsStrength() const
{
    return m_iGPSStrength;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setGPSStrength(int iStrength)
{
    m_iGPSStrength = iStrength;
    emit gpsStrengthChanged();
    emit gpsStatusChanged();
}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &DroneBase::initialPosition() const
{
    return m_initialPosition;
}

//-------------------------------------------------------------------------------------------------

const QGeoCoordinate &DroneBase::position() const
{
    return m_position;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setPosition(const QGeoCoordinate &position)
{
    m_position = position;
    emit positionChanged();
}

//-------------------------------------------------------------------------------------------------

double DroneBase::heading() const
{
    return m_dHeading;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setHeading(double dHeading)
{
    m_dHeading = dHeading;
    emit headingChanged();
}

//-------------------------------------------------------------------------------------------------

int DroneBase::batteryStatus() const
{
    if (m_iBatteryLevel <= 33)
        return CRITICAL;
    else
    if ((m_iBatteryLevel > 33) && (m_iBatteryLevel <= 66))
        return WARNING;
    return NOMINAL;
}

//-------------------------------------------------------------------------------------------------

int DroneBase::gpsStatus() const
{
    if (m_iGPSStrength <= 33)
        return CRITICAL;
    else
    if ((m_iGPSStrength > 33) && (m_iGPSStrength <= 66))
        return WARNING;
    return NOMINAL;
}

//-------------------------------------------------------------------------------------------------

int DroneBase::globalStatus() const
{
    return qMax(batteryStatus(), gpsStatus());
}

//-------------------------------------------------------------------------------------------------

int DroneBase::state() const
{
    return (int)m_eState;
}

//-------------------------------------------------------------------------------------------------

QString DroneBase::stateText() const
{
    if (m_eState == FLYING)
        return tr("Flying");
    return tr("IDLE");
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setState(int iState)
{
    m_eState = (DroneBase::State)iState;
    emit stateChanged();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setEditMode(int iMode)
{
    m_eEditMode = (DroneBase::EditMode)iMode;
    emit editModeChanged();
}

//-------------------------------------------------------------------------------------------------

int DroneBase::editMode() const
{
    return (int)m_eEditMode;
}

//-------------------------------------------------------------------------------------------------

WayPointModel *DroneBase::missionPlanModel() const
{
    return m_pMissionPlanModel;
}

//-------------------------------------------------------------------------------------------------

WayPointModel *DroneBase::safetyModel() const
{
    return m_pSafetyModel;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::clearMissionPlan()
{
    if (m_pMissionPlanModel != nullptr)
        m_pMissionPlanModel->clear();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::clearSafety()
{
    if (m_pSafetyModel != nullptr)
        m_pSafetyModel->clear();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::addCoordinateToMissionPlan(const QGeoCoordinate &geoCoordinate)
{
    if (m_pMissionPlanModel != nullptr)
        m_pMissionPlanModel->addCoordinate(geoCoordinate);
}

//-------------------------------------------------------------------------------------------------

void DroneBase::addCoordinateToSafety(const QGeoCoordinate &geoCoordinate)
{
    if (m_pSafetyModel != nullptr)
        m_pSafetyModel->addCoordinate(geoCoordinate);
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setMissionPlanPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord)
{
    if (m_pMissionPlanModel != nullptr)
        m_pMissionPlanModel->setPointPosition(iPointIndex, geoCoord);
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setSafetyPointPosition(int iPointIndex, const QGeoCoordinate &geoCoord)
{
    if (m_pSafetyModel != nullptr)
        m_pSafetyModel->setPointPosition(iPointIndex, geoCoord);
}

//-------------------------------------------------------------------------------------------------

void DroneBase::removeCoordinateFromSafetyPlanAtIndex(int iPointIndex)
{
    if (m_pSafetyModel != nullptr)
        m_pSafetyModel->removeCoordinateAtIndex(iPointIndex);
}

//-------------------------------------------------------------------------------------------------

void DroneBase::removeCoordinateFromMissionPlanAtIndex(int iPointIndex)
{
    if (m_pMissionPlanModel != nullptr)
        m_pMissionPlanModel->removeCoordinateAtIndex(iPointIndex);
}


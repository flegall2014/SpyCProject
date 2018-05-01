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
    connect(this, &DroneBase::batteryStatusChanged, this, &DroneBase::onGlobalStatusChanged, Qt::QueuedConnection);
    connect(this, &DroneBase::gpsStrengthChanged, this, &DroneBase::onGlobalStatusChanged, Qt::QueuedConnection);
    connect(this, &DroneBase::positionStatusChanged, this, &DroneBase::onGlobalStatusChanged, Qt::QueuedConnection);
}

//-------------------------------------------------------------------------------------------------

DroneBase::DroneBase(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPosition, QObject *parent) :
    QObject(parent), m_sDroneUID(sDroneUID), m_sVideoUrl(sVideoUrl), m_initialPosition(initialPosition), m_position(initialPosition)
{
    // Mission plan model
    m_pMissionPlanModel = new WayPointModel(this);
    m_pSafetyModel = new WayPointModel(this);
    connect(this, &DroneBase::batteryStatusChanged, this, &DroneBase::onGlobalStatusChanged, Qt::QueuedConnection);
    connect(this, &DroneBase::gpsStrengthChanged, this, &DroneBase::onGlobalStatusChanged, Qt::QueuedConnection);
    connect(this, &DroneBase::positionStatusChanged, this, &DroneBase::onGlobalStatusChanged, Qt::QueuedConnection);
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
    updateBatteryStatus();
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
    updateGPSStatus();
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
    return m_eBatteryStatus;
}

void DroneBase::setBatteryStatus(int iBatteryStatus)
{
    m_eBatteryStatus = (Status)iBatteryStatus;
    emit batteryStatusChanged();
}

//-------------------------------------------------------------------------------------------------

int DroneBase::gpsStatus() const
{
    return m_eGPSStatus;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setGPSStatus(int iGPSStatus)
{
    m_eGPSStatus = (Status)iGPSStatus;
    emit gpsStatusChanged();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setGlobalStatus(const Status &eStatus)
{
    m_eGlobalStatus = eStatus;
    emit globalStatusChanged();
}

//-------------------------------------------------------------------------------------------------

int DroneBase::globalStatus() const
{
    return m_eGlobalStatus;
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

//-------------------------------------------------------------------------------------------------

void DroneBase::onGlobalStatusChanged()
{
    Status eNewGlobalStatus = (Status)qMax(batteryStatus(), gpsStatus());
    if (eNewGlobalStatus != m_eGlobalStatus)
        setGlobalStatus(eNewGlobalStatus);
}

//-------------------------------------------------------------------------------------------------

void DroneBase::updateBatteryStatus()
{
    Status eBatteryStatus = NOMINAL;
    if ((m_iBatteryLevel > 33) && (m_iBatteryLevel <= 66))
        eBatteryStatus = WARNING;
    else
    if (m_iBatteryLevel <= 33)
        eBatteryStatus = CRITICAL;
    if (eBatteryStatus != m_eBatteryStatus)
        setBatteryStatus(eBatteryStatus);
}

//-------------------------------------------------------------------------------------------------

void DroneBase::updateGPSStatus()
{
    Status eGPSStatus = NOMINAL;
    if ((m_iGPSStrength > 33) && (m_iGPSStrength <= 66))
        eGPSStatus = WARNING;
    else
    if (m_iGPSStrength <= 33)
        eGPSStatus = CRITICAL;
    if (eGPSStatus != m_eGPSStatus)
        setGPSStatus(eGPSStatus);
}

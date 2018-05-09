// Qt
#include <QDebug>

// Application
#include "dronebase.h"
#include <drone.h>
#include "waypointmodel.h"
#include "alertmodel.h"
#include "gallerymodel.h"
#include "settingcontroller.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

DroneBase::DroneBase(QObject *parent) : QObject(parent)
{
    m_eWorkMode = m_eDefaultWorkMode;
}

//-------------------------------------------------------------------------------------------------

DroneBase::DroneBase(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPosition, QObject *parent) :
    QObject(parent), m_sDroneUID(sDroneUID), m_sVideoUrl(sVideoUrl), m_initialPosition(initialPosition), m_position(initialPosition)
{
    m_eWorkMode = m_eDefaultWorkMode;
}

//-------------------------------------------------------------------------------------------------

DroneBase::~DroneBase()
{

}

//-------------------------------------------------------------------------------------------------

void DroneBase::initialize(const QMap<int, QVariant> &mSettings)
{
    // Set settings
    m_mSettings = mSettings;

    // Mission plan model
    m_pMissionPlanModel = new WayPointModel(this);
    m_pSafetyModel = new WayPointModel(this);
    m_pAlertModel = new AlertModel(this);
    m_pGalleryModel = new GalleryModel(m_mSettings[SettingController::GALLERY_PATH].toString(), this);
    connect(this, &DroneBase::batteryStatusChanged, this, &DroneBase::onGlobalStatusChanged, Qt::QueuedConnection);
    connect(this, &DroneBase::gpsStrengthChanged, this, &DroneBase::onGlobalStatusChanged, Qt::QueuedConnection);
    connect(this, &DroneBase::positionStatusChanged, this, &DroneBase::onGlobalStatusChanged, Qt::QueuedConnection);
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

//-------------------------------------------------------------------------------------------------

void DroneBase::setBatteryStatus(int iBatteryStatus)
{
    m_eBatteryStatus = (Status)iBatteryStatus;
    if ((m_eBatteryStatus == DroneBase::WARNING) || (m_eBatteryStatus == DroneBase::CRITICAL))
        m_pAlertModel->addAlert(Alert(BATTERY, m_eBatteryStatus, m_eBatteryStatus == DroneBase::WARNING ? tr("Low battery level") : tr("Critical battery level")));
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
    if ((m_eGPSStatus == DroneBase::WARNING) || (m_eGPSStatus == DroneBase::CRITICAL))
        m_pAlertModel->addAlert(Alert(BATTERY, m_eGPSStatus, m_eGPSStatus == DroneBase::WARNING ? tr("Low GPS strength") : tr("Critical GPS strength")));
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

int DroneBase::workMode() const
{
    return (int)m_eWorkMode;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setWorkMode(int iMode)
{
    //qDebug() << "SETTING WORK MODE TO " << iMode;
    m_eWorkMode = (DroneBase::WorkMode)iMode;
    emit workModeChanged();
}

//-------------------------------------------------------------------------------------------------

int DroneBase::defaultWorkMode() const
{
    return (int)m_eDefaultWorkMode;
}

//-------------------------------------------------------------------------------------------------

int DroneBase::currentExclusionShape() const
{
    return (int)m_eExclusionShape;
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setCurrentExclusionShape(int iExclusionShape)
{
    m_eExclusionShape = (ExclusionShape)iExclusionShape;
    emit currentExclusionShapeChanged();
}

//-------------------------------------------------------------------------------------------------

void DroneBase::setDefaultWorkMode()
{
    qDebug() << "SETTING DEFAULT WORK MODE";
    m_eWorkMode = m_eDefaultWorkMode;
    emit workModeChanged();
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

AlertModel *DroneBase::alertModel() const
{
    return m_pAlertModel;
}

//-------------------------------------------------------------------------------------------------

GalleryModel *DroneBase::galleryModel() const
{
    return m_pGalleryModel;
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

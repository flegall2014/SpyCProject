// Qt
#include <QTime>
#include <QDebug>

// Application
#include "dronemanager.h"
#include "drone.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

DroneManager::DroneManager(QObject *pParent) : IBasePlugin(pParent)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    m_droneTimer.setInterval(1000);
    m_droneTimer.setSingleShot(true);
    connect(&m_droneTimer, &QTimer::timeout, this, &DroneManager::onDroneTimeOut, Qt::QueuedConnection);
}

//-------------------------------------------------------------------------------------------------

DroneManager::~DroneManager()
{

}

//-------------------------------------------------------------------------------------------------

QString DroneManager::name() const
{
    return "DroneManager";
}

//-------------------------------------------------------------------------------------------------

float DroneManager::version() const
{
    return 1.0;
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onStartDroneDetection()
{
    m_droneTimer.start();
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onDroneTimeOut()
{
    QStringList lVideos;
    lVideos << "file:///D:/projects/SpycProject/SpyC/video/video1.mp4" <<
        "file:///D:/projects/SpycProject/SpyC/video/video2.mp4" <<
        "file:///D:/projects/SpycProject/SpyC/video/video3.mp4";

    QVector<double> vLatitudes = QVector<double>() << 48.856614 << 40.7127753 << 9.641185499999999;
    QVector<double> vLongitudes = QVector<double>() << 2.3522219000000177 << -74.0059728 << -13.57840120000003;
    static int iDroneCount = 0;
    double dLatitude = vLatitudes[iDroneCount%3];
    double dLongitude = vLongitudes[iDroneCount%3];
    QGeoCoordinate initialPos(dLatitude, dLongitude);

    // Create enw drone
    QString sDroneUID = QString("DRONE %1").arg(iDroneCount);
    if ((m_hDrones[sDroneUID] == nullptr) && (iDroneCount < 3))
    {
        Drone *pDrone = new Drone(sDroneUID, lVideos[iDroneCount%3], initialPos, this);
        connect(pDrone, &Drone::positionChanged, this, &DroneManager::positionChanged, Qt::QueuedConnection);
        connect(pDrone, &Drone::batteryLevelChanged, this, &DroneManager::batteryLevelChanged, Qt::QueuedConnection);
        connect(pDrone, &Drone::gpsStrengthChanged, this, &DroneManager::gpsStrengthChanged, Qt::QueuedConnection);
        connect(pDrone, &Drone::missionPlanChanged, this, &DroneManager::missionPlanChanged, Qt::QueuedConnection);
        connect(pDrone, &Drone::safetyChanged, this, &DroneManager::safetyChanged, Qt::QueuedConnection);
        connect(pDrone, &Drone::landingPlanChanged, this, &DroneManager::landingPlanChanged, Qt::QueuedConnection);
        connect(pDrone, &Drone::exclusionAreaChanged, this, &DroneManager::exclusionAreaChanged, Qt::QueuedConnection);
        connect(pDrone, &Drone::droneError, this, &DroneManager::droneError, Qt::QueuedConnection);
        connect(pDrone, &Drone::failSafeDone, this, &DroneManager::failSafeDone, Qt::QueuedConnection);
        m_hDrones[pDrone->uid()] = pDrone;
        emit newDroneAvailable(pDrone->videoUrl(), pDrone->initialPosition(), pDrone->uid());
        m_droneTimer.start();
        iDroneCount++;
    }
}

//-------------------------------------------------------------------------------------------------

void DroneManager::setMissionPlan(const QString &sDroneUID, const QGeoPath &missionPlan)
{
    Drone *pTargetDrone = m_hDrones[sDroneUID];
    if (pTargetDrone != nullptr)
        pTargetDrone->setMissionPlan(missionPlan);
}

//-------------------------------------------------------------------------------------------------

void DroneManager::setSafety(const QString &sDroneUID, const QGeoPath &safety)
{
    Drone *pTargetDrone = m_hDrones[sDroneUID];
    if (pTargetDrone != nullptr)
        pTargetDrone->setSafety(safety);
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onTakeOffRequest(const QString &sDroneUID)
{
    Drone *pTargetDrone = m_hDrones[sDroneUID];
    if (pTargetDrone != nullptr)
        pTargetDrone->takeOff();
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onFailSafeRequest(const QString &sDroneUID)
{
    Drone *pTargetDrone = m_hDrones[sDroneUID];
    if (pTargetDrone != nullptr)
        pTargetDrone->failSafe();
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onUploadMissionPlan(const QGeoPath &path, const QString &sDroneUID)
{
    // Retrieve target drone
    Drone *pDrone = m_hDrones[sDroneUID];
    if (pDrone != nullptr)
        pDrone->setMissionPlan(path);
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onUploadSafety(const QGeoPath &path, const QString &sDroneUID)
{
    // Retrieve target drone
    Drone *pDrone = m_hDrones[sDroneUID];
    if (pDrone != nullptr)
        pDrone->setSafety(path);
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onUploadLandingPlan(const QGeoPath &path, const QString &sDroneUID)
{
    // Retrieve target drone
    Drone *pDrone = m_hDrones[sDroneUID];
    if (pDrone != nullptr)
        pDrone->setLandingPlan(path);
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onUploadExclusionArea(const QList<QGeoPath> &lExclusionArea, const QString &sDroneUID)
{
    // Retrieve target drone
    Drone *pDrone = m_hDrones[sDroneUID];
    if (pDrone != nullptr)
        pDrone->setExclusionArea(lExclusionArea);
}

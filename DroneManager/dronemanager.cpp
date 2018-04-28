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
    connect(&m_droneTimer, &QTimer::timeout, this, &DroneManager::onDroneTimeOut);
    m_droneTimer.start();
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

void DroneManager::onDroneTimeOut()
{
    QStringList lVideos;
    lVideos << "file:///D:/projects/SpycProject/SpyC/video/video1.mp4" <<
        "file:///D:/projects/SpycProject/SpyC/video/video2.mp4" <<
        "file:///D:/projects/SpycProject/SpyC/video/video3.mp4";

    QVector<double> vLatitudes = QVector<double>() << 48.856614 << 40.7127753 << 9.641185499999999;
    QVector<double> vLongitudes = QVector<double>() << 2.3522219000000177 << -74.0059728 << -13.57840120000003;
    static int iDroneCount = 0;
    double dLatitude = vLatitudes[iDroneCount];
    double dLongitude = vLongitudes[iDroneCount];
    QGeoCoordinate initialPos(dLatitude, dLongitude);

    // Create enw drone
    QString sDroneUID = QString("DRONE%1").arg(iDroneCount);
    if ((m_hDrones[sDroneUID] == nullptr) && (iDroneCount < 3))
    {
        Drone *pDrone = new Drone(sDroneUID, lVideos[iDroneCount%3], initialPos, this);
        connect(pDrone, &Drone::positionChanged, this, &DroneManager::positionChanged);
        connect(pDrone, &Drone::batteryLevelChanged, this, &DroneManager::batteryLevelChanged);
        connect(pDrone, &Drone::gpsStrengthChanged, this, &DroneManager::gpsStrengthChanged);
        connect(pDrone, &Drone::missionPlanChanged, this, &DroneManager::missionPlanChanged);
        connect(pDrone, &Drone::safetyChanged, this, &DroneManager::safetyChanged);
        connect(pDrone, &Drone::droneError, this, &DroneManager::droneError);
        connect(pDrone, &Drone::failSafeDone, this, &DroneManager::failSafeDone);
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

void DroneManager::onTakeOff(const QString &sDroneUID)
{
    Drone *pTargetDrone = m_hDrones[sDroneUID];
    if (pTargetDrone != nullptr)
        pTargetDrone->takeOff();
}

//-------------------------------------------------------------------------------------------------

void DroneManager::onFailSafe(const QString &sDroneUID)
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

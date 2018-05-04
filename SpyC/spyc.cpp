// Qt
#include <qqml.h>
#include <QQmlContext>
#include <QQuickItem>
#include <QDebug>

// Application
#include "spyc.h"
#include "pluginloader.h"
#include "mastercontroller.h"
#include "missionplancontroller.h"
#include "settingcontroller.h"
#include "flightcontroller.h"
#include "dronemodel.h"
#include "dronebase.h"
#include "waypointmodel.h"
#include "alertmodel.h"
#include "snapshotmodel.h"

SpyC *SpyC::sInstance = nullptr;

//-------------------------------------------------------------------------------------------------

SpyC::SpyC(QObject *parent) : QObject(parent)
{    
    // Register types
    registerTypes();

    // Plugin loader
    m_pPluginLoader = new PluginLoader(this);

    // Drone controller
    m_pMasterController = new MasterController(this);

    // Set context properties
    setContextProperties();
}

//-------------------------------------------------------------------------------------------------

SpyC::~SpyC()
{
    qDebug() << "DESTROYING SPYC";
}

//-------------------------------------------------------------------------------------------------

SpyC *SpyC::instance()
{
    if (sInstance == nullptr)
        sInstance = new SpyC;
    return sInstance;
}

//-------------------------------------------------------------------------------------------------

bool SpyC::startup(const QStringList &lArgs)
{
    // Start plugin loader
    if (!m_pPluginLoader->startup(lArgs))
        return false;

    // Start controller
    if (!m_pMasterController->startup())
        return false;

    // Set model on drone controller
    QVector<QObject *> vPlugins = m_pPluginLoader->getPlugins();
    foreach (QObject *pPlugin, vPlugins)
    {
        Model::DroneManager *pDroneManager = qobject_cast<Model::DroneManager *>(pPlugin);
        if (pDroneManager != nullptr)
            m_pMasterController->setModel(pDroneManager);
    }

    // Launch UI
    launchUI();

    return true;
}

//-------------------------------------------------------------------------------------------------

void SpyC::shutdown()
{
    m_pMasterController->shutdown();
}

//-------------------------------------------------------------------------------------------------

void SpyC::launchUI()
{
    m_engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
}

//-------------------------------------------------------------------------------------------------

void SpyC::registerTypes()
{
    // Register types
    qmlRegisterType<SpyC>("Components", 1, 0, "SpyC");
    qmlRegisterType<DroneBase>("Components", 1, 0, "DroneBase");
    qmlRegisterType<MasterController>("Components", 1, 0, "MasterController");
    qmlRegisterType<SettingController>("Commponent", 1, 0, "SettingController");
    qmlRegisterType<MissionPlanController>("Components", 1, 0, "MissionPlanController");
    qmlRegisterType<FlightController>("Components", 1, 0, "FlightController");
    qmlRegisterType<DroneModel>("Components", 1, 0, "DroneModel");
    qmlRegisterType<WayPointModel>("Components", 1, 0, "WayPointModel");
    qmlRegisterType<AlertModel>("Components", 1, 0, "AlertModel");
    qmlRegisterType<SnapShotModelFilter>("Components", 1, 0, "SnapShotModel");
}

//-------------------------------------------------------------------------------------------------

void SpyC::setContextProperties()
{
    m_engine.rootContext()->setContextProperty("MASTERCONTROLLER", m_pMasterController);
}

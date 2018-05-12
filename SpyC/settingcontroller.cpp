// Qt
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include <QStandardPaths>
#include <QSettings>
#include <QLocale>

// Application
#include "settingcontroller.h"

//-------------------------------------------------------------------------------------------------

SettingController::SettingController(QObject *pParent) : QObject(pParent)
{

}

//-------------------------------------------------------------------------------------------------

SettingController::~SettingController()
{

}

//-------------------------------------------------------------------------------------------------

bool SettingController::startup(const QStringList &lArgs)
{
    Q_UNUSED(lArgs);

    loadSettings();
    return true;
}

//-------------------------------------------------------------------------------------------------

void SettingController::shutdown()
{

}

//-------------------------------------------------------------------------------------------------

void SettingController::setMasterController(MasterController *pMasterController)
{
    m_pMasterController = pMasterController;
}

//-------------------------------------------------------------------------------------------------

void SettingController::applyLanguage(const QString &sLang)
{
    setLangString(sLang);
    if (sLang == "FR")
        setLanguage(QLocale::French);
    else
    if (sLang == "US")
        setLanguage(QLocale::English);
    else
    if (sLang == "SD")
        setLanguage(QLocale::Arabic);
}

//-------------------------------------------------------------------------------------------------

QString SettingController::snapShotPath(const QString &sDroneUID) const
{
    QDateTime curDateTime = QDateTime::currentDateTime();
    QString sTimeStamp = QString("%1_%2_%3_%4_%5_%6").arg(curDateTime.date().day()).arg(curDateTime.date().month()).
            arg(curDateTime.date().year()).arg(curDateTime.time().hour()).arg(curDateTime.time().minute()).
            arg(curDateTime.time().second());
    QString sGalleryDir = QDir(m_sGalleryPath).absoluteFilePath(sDroneUID);
    sGalleryDir.replace(" ", "_");
    QDir dGalleryDir(sGalleryDir);
    dGalleryDir.mkpath(dGalleryDir.absolutePath());
    QString sGalleryFile = dGalleryDir.absoluteFilePath("snapshot_%1_%2.jpg").arg(sDroneUID).arg(sTimeStamp);
    return sGalleryFile;
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::army() const
{
    return m_sArmy;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setArmy(const QString &sArmy)
{
    if (sArmy != m_sArmy)
    {
        m_sArmy = sArmy;
        emit armyChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::unit() const
{
    return m_sUnit;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setUnit(const QString &sUnit)
{
    if (sUnit != m_sUnit)
    {
        m_sUnit = sUnit;
        emit unitChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::mission() const
{
    return m_sMission;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMission(const QString &sMission)
{
    if (sMission != m_sMission)
    {
        m_sMission = sMission;
        emit missionChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::operatorName() const
{
    return m_sOperator;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setOperatorName(const QString &sName)
{
    if (sName != m_sOperator)
    {
        m_sOperator = sName;
        emit operatorNameChanged();
    }
}

//-------------------------------------------------------------------------------------------------

int SettingController::language() const
{
    return (int)m_eLanguage;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLanguage(int iLanguage)
{
    if ((QLocale::Language)iLanguage != m_eLanguage)
    {
        m_eLanguage = (QLocale::Language)iLanguage;
        emit languageChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::langString() const
{
    return m_sLangString;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLangString(const QString &sLangString)
{
    if (sLangString != m_sLangString)
    {
        m_sLangString = sLangString;
        emit langStringChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::mapPath() const
{
    return m_sMapPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMapPath(const QString &sMapPath)
{
    if (sMapPath != m_sMapPath)
    {
        m_sMapPath = sMapPath;
        emit mapPathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::missionPath() const
{
    return m_sMissionPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMissionPath(const QString &sMissionPath)
{
    if (sMissionPath != m_sMissionPath)
    {
        m_sMissionPath = sMissionPath;
        emit missionPathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::logPath() const
{
    return m_sLogPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLogPath(const QString &sLogPath)
{
    if (sLogPath != m_sLogPath)
    {
        m_sLogPath = sLogPath;
        emit logPathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::alertPath() const
{
    return m_sAlertPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setAlertPath(const QString &sAlertPath)
{
    if (sAlertPath != m_sAlertPath)
    {
        m_sAlertPath = sAlertPath;
        emit alertPathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::galleryPath() const
{
    return m_sGalleryPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setGalleryPath(const QString &sGalleryPath)
{
    if (sGalleryPath != m_sGalleryPath)
    {
        m_sGalleryPath = sGalleryPath;
        emit galleryPathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

QMap<int, QVariant> SettingController::allSettings()
{
    QMap<int, QVariant> mAllSettings;
    mAllSettings[ARMY] = m_sArmy;
    mAllSettings[UNIT] = m_sUnit;
    mAllSettings[MISSION] = m_sMission;
    mAllSettings[OPERATOR] = m_sOperator;
    mAllSettings[LANGUAGE] = m_eLanguage;
    mAllSettings[LANGUAGE_STRING] = m_sLangString;
    mAllSettings[MAP_PATH] = m_sMapPath;
    mAllSettings[MISSION_PATH] = m_sMissionPath;
    mAllSettings[LOG_PATH] = m_sLogPath;
    mAllSettings[ALERT_PATH] = m_sAlertPath;
    mAllSettings[GALLERY_PATH] = m_sGalleryPath;
    return mAllSettings;
}

//-------------------------------------------------------------------------------------------------

void SettingController::loadSettings()
{
    QDir baseDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    QSettings settings;
    QString sArmy = settings.value("/user/army").toString();
    if (sArmy.simplified().isEmpty())
        sArmy = tr("Army");
    m_sArmy = sArmy;

    QString sUnit = settings.value("/user/unit").toString();
    if (sUnit.simplified().isEmpty())
        sUnit = tr("Unit");
    m_sUnit = sUnit;

    QString sMission = settings.value("/user/mission").toString();
    if (sMission.simplified().isEmpty())
        sMission = tr("Mission");
    m_sMission = sMission;

    QString sOperator = settings.value("/user/operator").toString();
    if (sOperator.simplified().isEmpty())
        sOperator = tr("Operator");
    m_sOperator = sOperator;

    QString sLangString = settings.value("/user/language").toString();
    if (sLangString.simplified().isEmpty())
        sLangString = "FR";
    applyLanguage(sLangString);

    QString sMapPath = settings.value("/user/maps").toString();
    if (sMapPath.simplified().isEmpty())
        sMapPath = baseDir.absoluteFilePath("maps");
    createDir(sMapPath);
    m_sMapPath = sMapPath;

    QString sMissionPath = settings.value("/user/mission").toString();
    if (sMissionPath.simplified().isEmpty())
        sMissionPath = baseDir.absoluteFilePath("mission");
    createDir(sMissionPath);
    m_sMissionPath = sMissionPath;

    QString sLogPath = settings.value("/user/logs").toString();
    if (sLogPath.simplified().isEmpty())
        sLogPath = baseDir.absoluteFilePath("logs");
    createDir(sLogPath);
    m_sLogPath = sLogPath;

    QString sAlertPath = settings.value("/user/alerts").toString();
    if (sAlertPath.simplified().isEmpty())
        sAlertPath = baseDir.absoluteFilePath("alerts");
    createDir(sAlertPath);
    m_sAlertPath = sAlertPath;

    QString sGalleryPath = settings.value("/user/gallery").toString();
    if (sGalleryPath.simplified().isEmpty())
        sGalleryPath = baseDir.absoluteFilePath("gallery");
    createDir(sGalleryPath);
    m_sGalleryPath = sGalleryPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::createDir(const QString &sDirPath)
{
    qDebug() << "CREATING DIR: " << sDirPath;
    QDir dir(sDirPath);
    if (!dir.exists())
      dir.mkpath(".");
}

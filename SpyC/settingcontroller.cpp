// Qt
#include <QDebug>

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

const QString &SettingController::army() const
{
    return m_sArmy;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setArmy(const QString &sArmy)
{
    m_sArmy = sArmy;
    emit armyChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::unit() const
{
    return m_sUnit;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setUnit(const QString &sUnit)
{
    m_sUnit = sUnit;
    emit unitChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::mission() const
{
    return m_sMission;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMission(const QString &sMission)
{
    m_sMission = sMission;
    emit missionChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::operatorName() const
{
    return m_sOperator;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setOperatorName(const QString &sName)
{
    m_sOperator = sName;
    emit operatorNameChanged();
}

//-------------------------------------------------------------------------------------------------

int SettingController::language() const
{
    return (int)m_eLanguage;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLanguage(int iLanguage)
{
    m_eLanguage = (QLocale::Language)iLanguage;
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::langString() const
{
    return m_sLangString;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLangString(const QString &sLangString)
{
    m_sLangString = sLangString;
    emit langStringChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::mapPath() const
{
    return m_sMapPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMapPath(const QString &sMapPath)
{
    m_sMapPath = sMapPath;
    emit mapPathChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::missionPath() const
{
    return m_sMissionPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setMissionPath(const QString &sMissionPath)
{
    m_sMissionPath = sMissionPath;
    emit missionPathChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::logPath() const
{
    return m_sLogPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setLogPath(const QString &sLogPath)
{
    m_sLogPath = sLogPath;
    emit logPathChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::alertPath() const
{
    return m_sAlertPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setAlertPath(const QString &sAlertPath)
{
    m_sAlertPath = sAlertPath;
    emit alertPathChanged();
}

//-------------------------------------------------------------------------------------------------

const QString &SettingController::snapShotPath() const
{
    return m_sSnapShotPath;
}

//-------------------------------------------------------------------------------------------------

void SettingController::setSnapShotPath(const QString &sSnapShotPath)
{
    m_sSnapShotPath = sSnapShotPath;
    emit snapShotPathChanged();
}

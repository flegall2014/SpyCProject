#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H

// Qt
#include <QObject>
#include <QLocale>

// Application
class MasterController;

class SettingController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString army READ army WRITE setArmy NOTIFY armyChanged)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(QString mission READ mission WRITE setMission NOTIFY missionChanged)
    Q_PROPERTY(QString operatorName READ operatorName WRITE setOperatorName NOTIFY operatorNameChanged)
    Q_PROPERTY(int language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString langString READ langString WRITE setLangString NOTIFY langStringChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    SettingController(QObject *pParent=nullptr);

    //! Destructor
    ~SettingController();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Set master controller
    void setMasterController(MasterController *pMasterController);

    //! Apply language
    Q_INVOKABLE void applyLanguage(const QString &sLang);

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return army
    const QString &army() const;

    //! Set army
    void setArmy(const QString &sArmy);

    //! Return unit
    const QString &unit() const;

    //! Set unit
    void setUnit(const QString &sUnit);

    //! Return mission
    const QString &mission() const;

    //! Set mission
    void setMission(const QString &sMission);

    //! Return operator
    const QString &operatorName() const;

    //! Set operator
    void setOperatorName(const QString &sName);

    //! Return language
    int language() const;

    //! Set language
    void setLanguage(int iLanguage);

    //! Return lang string
    const QString &langString() const;

    //! Set lang string
    void setLangString(const QString &sLangString);

    //! Return map path
    const QString &mapPath() const;

    //! Set map path
    void setMapPath(const QString &sMapPath);

    //! Return mission path
    const QString &missionPath() const;

    //! Set mission path
    void setMissionPath(const QString &sMissionPath);

    //! Return log path
    const QString &logPath() const;

    //! Set log path
    void setLogPath(const QString &sLogPath);

    //! Return alert path
    const QString &alertPath() const;

    //! Set alert path
    void setAlertPath(const QString &sAlertPath);

    //! Return snapshot path
    const QString &snapShotPath() const;

    //! Set snapshot path
    void setSnapShotPath(const QString &sSnapShotPath);

private:
    //! Master controller
    MasterController *m_pMasterController = nullptr;

    //! Army
    QString m_sArmy = "";

    //! Unit
    QString m_sUnit = "";

    //! Mission
    QString m_sMission = "";

    //! Operator
    QString m_sOperator = "";

    //! Language
    QLocale::Language m_eLanguage = QLocale::French;

    //! Language string
    QString m_sLangString = "FR";

    //! Map path
    QString m_sMapPath = "";

    //! Mission path
    QString m_sMissionPath = "";

    //! Log path
    QString m_sLogPath = "";

    //! Alert path
    QString m_sAlertPath = "";

    //! Snapshot path
    QString m_sSnapShotPath = "";

signals:
    //! Army changed
    void armyChanged();

    //! Unit changed
    void unitChanged();

    //! Mission changed
    void missionChanged();

    //! Operator name changed
    void operatorNameChanged();

    //! Language changed
    void languageChanged();

    //! Language string changed
    void langStringChanged();

    //! Map path changed
    void mapPathChanged();

    //! Mission path changed
    void missionPathChanged();

    //! Log path changed
    void logPathChanged();

    //! Alert path changed
    void alertPathChanged();

    //! Snapshot path changed
    void snapShotPathChanged();
};

#endif // SETTINGCONTROLLER_H

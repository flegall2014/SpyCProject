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
    Q_PROPERTY(QString langString READ langString WRITE setLangString NOTIFY langStringChanged)
    Q_PROPERTY(QString mapPath READ mapPath WRITE setMapPath NOTIFY mapPathChanged)
    Q_PROPERTY(QString missionPath READ missionPath WRITE setMissionPath NOTIFY missionPathChanged)
    Q_PROPERTY(QString logPath READ logPath WRITE setLogPath NOTIFY logPathChanged)
    Q_PROPERTY(QString alertPath READ alertPath WRITE setAlertPath NOTIFY alertPathChanged)
    Q_PROPERTY(QString galleryPath READ galleryPath WRITE setGalleryPath NOTIFY galleryPathChanged)
    Q_PROPERTY(int hand READ hand WRITE setHand NOTIFY handChanged)
    Q_ENUMS(Setting)
    Q_ENUMS(UIOrientation)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Setting type
    enum Setting {ARMY=Qt::UserRole+1, UNIT, MISSION, OPERATOR, LANGUAGE_STRING,
                 MAP_PATH, MISSION_PATH, LOG_PATH, ALERT_PATH, GALLERY_PATH};

    //! UI orientation
    enum UIOrientation {RIGHT_HAND=Qt::UserRole+1, LEFT_HAND};

    //! Constructor
    SettingController(QObject *pParent=nullptr);

    //! Destructor
    ~SettingController();

    //-------------------------------------------------------------------------------------------------
    // IService interface
    //-------------------------------------------------------------------------------------------------

    //! Startup
    virtual bool startup(const QStringList &lArgs);

    //! Shutdown
    virtual void shutdown();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Set master controller
    void setMasterController(MasterController *pMasterController);

    //! Apply language
    Q_INVOKABLE void applyLanguage(const QString &sLang);

    //! Return a gallery path given a drone UID
    Q_INVOKABLE QString snapShotPath(const QString &sDroneUID) const;

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

    //! Return gallery path
    const QString &galleryPath() const;

    //! Set gallery path
    void setGalleryPath(const QString &sGalleryPath);

    //! Return hand
    int hand() const;

    //! Set hand
    void setHand(int iHand);

    //! Return all settings
    QMap<int, QVariant> allSettings();

private:
    //! Load settings
    void loadSettings();

    //! Save settings
    void saveSettings();

    //! Create dir
    void createDir(const QString &sDirPath);

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

    //! Language string
    QString m_sLangString = "US";

    //! Map path
    QString m_sMapPath = "";

    //! Mission path
    QString m_sMissionPath = "";

    //! Log path
    QString m_sLogPath = "";

    //! Alert path
    QString m_sAlertPath = "";

    //! Gallery path
    QString m_sGalleryPath = "";

    //! UI orientation
    UIOrientation m_eHand = RIGHT_HAND;

signals:
    //! Army changed
    void armyChanged();

    //! Unit changed
    void unitChanged();

    //! Mission changed
    void missionChanged();

    //! Operator name changed
    void operatorNameChanged();

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

    //! Gallery path changed
    void galleryPathChanged();

    //! Hand changed
    void handChanged();
};

Q_DECLARE_METATYPE(SettingController::Setting)
Q_DECLARE_METATYPE(SettingController::UIOrientation)

#endif // SETTINGCONTROLLER_H

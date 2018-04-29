#ifndef SPYC_H
#define SPYC_H

// Qt
#include <QObject>
#include <QQmlApplicationEngine>
class QQuickItem;

// Application
#include "iservice.h"
class PluginLoader;
class MasterController;

class SpyC : public QObject, public IService
{
    Q_OBJECT
    Q_ENUMS(MsgType)
    Q_ENUMS(DialogType)

public:
    //! Message type
    enum MsgType {INFORMATION=Qt::UserRole+1, WARNING, CRITICAL};

    //! Dialog type
    enum DialogType {CONFIRM_TAKE_OFF=Qt::UserRole+1, CONFIRM_FAILSAFE, EMPTY_MISSION_PLAN_ERROR,
                    EMPTY_SAFETY_ERROR, MISSION_PLAN_VALIDATION, NOT_ENOUGH_POINT_IN_MISSION_PLAN,
                    NOT_ENOUGH_POINT_IN_SAFETY, SAFETY_VALIDATION};

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    SpyC(QObject *parent=nullptr);

    //! Destructor
    virtual ~SpyC();

    //! Return instance
    static SpyC *instance();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Start server
    virtual bool startup(const QStringList &lArgs=QStringList());

    //! Stop server
    virtual void shutdown();

private:
    //! Register types
    void registerTypes();

    //! Set context properties
    void setContextProperties();

private:
    //! Launch UI
    void launchUI();

private:
    //! Plugin loader
    PluginLoader *m_pPluginLoader = nullptr;

    //! Drone controller
    MasterController *m_pMasterController = nullptr;

    //! Main view
    QQmlApplicationEngine m_engine;

    //! SpyC instance
    static SpyC *sInstance;
};

#endif // SPYC_H

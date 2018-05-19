#ifndef BATTERYCONTROLLER_H
#define BATTERYCONTROLLER_H

// Qt
#include <QObject>

// Application
#include "iservice.h"
class MasterController;

class BatteryController : public QObject, public IService
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    explicit BatteryController(QObject *pParent=nullptr);

    //! Destructor
    ~BatteryController();

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

    // Set master controller
    void setMasterController(MasterController *pMasterController);

private:
    //! Master controller
    MasterController *m_pMasterController = nullptr;

public slots:
    //! Battery level changed
    void onBatteryLevelChanged(int iBatteryLevel, const QString &sDroneUID);

    //! Return level changed
    void onReturnLevelChanged(int iReturnLevel, const QString &sDroneUID);
};

#endif // BATTERYCONTROLLER_H

#ifndef GPSCONTROLLER_H
#define GPSCONTROLLER_H

// Qt
#include <QObject>

// Application
#include "iservice.h"
class MasterController;

class GPSController : public QObject, public IService
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    explicit GPSController(QObject *pParent=nullptr);

    //! Destructor
    ~GPSController();

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
    //! GPS strength changed
    void onGPSStrengthChanged(int iGPSStrength, const QString &sDroneUID);
};

#endif // GPSCONTROLLER_H

#ifndef FLIGHTCONTROLLER_H
#define FLIGHTCONTROLLER_H

// Qt
#include <QObject>

// Application
class MasterController;

class FlightController : public QObject
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    explicit FlightController(QObject *pParent=nullptr);

    //! Destructor
    ~FlightController();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    // Set master controller
    void setMasterController(MasterController *pMasterController);

    //! Take off
    void takeOff(const QString &sDroneUID);

    //! Fail safe
    void failSafe(const QString &sDroneUID);

private:
    //! Master controller
    MasterController *m_pMasterController = nullptr;

public slots:
    //! Fail safe done
    void onFailSafeDone(const QString &sDroneUID);

signals:
    //! Send a take off request
    void takeOffRequest(const QString &sDroneUID);

    //! Send a failsafe request
    void failSafeRequest(const QString &sDroneUID);
};

#endif // FLIGHTCONTROLLER_H

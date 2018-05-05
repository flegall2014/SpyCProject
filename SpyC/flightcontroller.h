#ifndef FLIGHTCONTROLLER_H
#define FLIGHTCONTROLLER_H

// Qt
#include <QObject>
#include <QGeoCoordinate>

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
    Q_INVOKABLE void takeOff(const QString &sDroneUID);

    //! Fail safe
    Q_INVOKABLE void failSafe(const QString &sDroneUID);

private:
    //! Master controller
    MasterController *m_pMasterController = nullptr;

public slots:    
    //! Position changed
    void onPositionChanged(const QGeoCoordinate &position, double dHeading, const QString &sDroneUID);

    //! Battery level changed
    void onBatteryLevelChanged(int iLevel, const QString &sDroneUID);

    //! GPS strength changed
    void onGPSStrengthChanged(int iStrength, const QString &sDroneUID);

    //! Fail safe done
    void onFailSafeDone(const QString &sDroneUID);

signals:
    //! Send a take off request
    void takeOffRequest(const QString &sDroneUID);

    //! Send a failsafe request
    void failSafeRequest(const QString &sDroneUID);
};

#endif // FLIGHTCONTROLLER_H

#ifndef GPSSIMULATOR_H
#define GPSSIMULATOR_H

// Qt
#include <QObject>
#include <QTimer>

// Application
#include "basesimulator.h"
#include "drone_manager_global.h"

namespace Model {
class DRONEMANAGERSHARED_EXPORT GPSSimulator : public BaseSimulator
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    GPSSimulator(const QString &sDroneUID, QObject *pParent=nullptr);

    //! Destructor
    ~GPSSimulator();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Start
    virtual void start();

    //! Stop
    virtual void stop();

private:
    //! GPS strength
    int m_iGPSStrength = 100;

    //! Repeat
    bool m_bRepeat = false;

public slots:
    //! Time out
    void onTimeOut();

signals:
    //! GPS strength changed
    void gpsStrengthChanged(int iLevel, const QString &sDroneUID);
};
}

#endif // GPSSIMULATOR_H

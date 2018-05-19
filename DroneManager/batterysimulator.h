#ifndef BATTERYSIMULATOR_H
#define BATTERYSIMULATOR_H

// Qt
#include <QObject>
#include <QTimer>

// Application
#include "basesimulator.h"
#include "drone_manager_global.h"

namespace Model {
class DRONEMANAGERSHARED_EXPORT BatterySimulator : public BaseSimulator
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    BatterySimulator(const QString &sDroneUID, QObject *pParent=nullptr);

    //! Destructor
    ~BatterySimulator();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Start
    virtual void start();

    //! Stop
    virtual void stop();

private:
    //! Battery level
    int m_iBatteryLevel = 100;

    //! Return level
    int m_iReturnLevel = 0;

    //! Repeat
    bool m_bRepeat = false;

public slots:
    //! Time out
    void onTimeOut();

signals:
    //! Battery level changed
    void batteryLevelChanged(int iLevel, const QString &sDroneUID);

    //! Return level changed
    void returnLevelChanged(int iLevel, const QString &sDroneUID);
};
}

#endif // BATTERYSIMULATOR_H

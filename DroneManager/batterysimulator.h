#ifndef BATTERYSIMULATOR_H
#define BATTERYSIMULATOR_H

// Qt
#include <QObject>
#include <QTimer>

// Application
#include "basesimulator.h"

namespace Model {
class BatterySimulator : public BaseSimulator
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

public slots:
    //! Time out
    void onTimeOut();

signals:
    //! Battery level changed
    void batteryLevelChanged(int iLevel, const QString &sDroneUID);
};
}

#endif // BATTERYSIMULATOR_H

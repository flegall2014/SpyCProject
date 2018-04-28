#ifndef GPSSIMULATOR_H
#define GPSSIMULATOR_H

// Qt
#include <QObject>
#include <QTimer>

// Application
#include "basesimulator.h"

namespace Model {
class GPSSimulator : public BaseSimulator
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
    int m_iGPSStrength = 0;

    //! Repeat
    bool m_bRepeat = false;

public slots:
    //! Time out
    void onTimeOut();

signals:
    //! GPS strength changed
    void gpsStrengthChanged(int iStrength, const QString &sDroneUID);
};
}

#endif // GPSSIMULATOR_H

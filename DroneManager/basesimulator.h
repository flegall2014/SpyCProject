#ifndef BASESIMULATOR_H
#define BASESIMULATOR_H

// Qt
#include <QObject>
#include <QTimer>

// Application
#include "drone_manager_global.h"

namespace Model {
class DRONEMANAGERSHARED_EXPORT BaseSimulator : public QObject
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    explicit BaseSimulator(const QString &sDroneUID, QObject *pParent=nullptr);

    //! Destructor
    virtual ~BaseSimulator() {}

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Start
    virtual void start() = 0;

    //! Stop
    virtual void stop() = 0;

protected:
    //! Drone UID
    QString m_sDroneUID = "";

    //! Timer
    QTimer m_timer;

public slots:
    //! Time out
    virtual void onTimeOut() {}
};
}

#endif // BASESIMULATOR_H

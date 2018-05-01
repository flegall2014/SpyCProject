#ifndef ALERT_H
#define ALERT_H

// Qt
#include <QVector>
#include <QObject>
#include <QTime>

// Application
#include "dronebase.h"

class Alert
{
public:
    //-------------------------------------------------------------------------------------------------
    // Constructors & destructors
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    Alert();

    //! Constructor
    Alert(const DroneBase::AlertType &eAlertType, const DroneBase::Status &eAlertLevel, const QString &sWhat);

    //! Destructor
    ~Alert();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return type
    const DroneBase::AlertType &type() const;

    //! Return level
    const DroneBase::Status &level() const;

    //! Return message
    const QString &what() const;

    //! Return date time
    QString dateTime() const;

private:
    //! Type
    DroneBase::AlertType m_eType = DroneBase::NO_ALERT;

    //! Level
    DroneBase::Status m_eLevel = DroneBase::NOMINAL;

    //! Message
    QString m_sWhat = "";

    //! Date
    QTime m_dateTime = QTime::currentTime();
};

#endif // ALERT_H

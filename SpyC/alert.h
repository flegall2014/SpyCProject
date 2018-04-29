#ifndef ALERT_H
#define ALERT_H

// Qt
#include <QVector>
#include <QObject>
#include <QTime>

namespace Model {
class Alert
{
public:
    //-------------------------------------------------------------------------------------------------
    // Constructors & destructors
    //-------------------------------------------------------------------------------------------------

    //! Alert level
    enum AlertLevel {UNDEFINED_LEVEL=Qt::UserRole+1, WARNING, CRITICAL};

    //! Alert type
    enum AlertType {UNDEFINED_ALERT=Qt::UserRole+1, BATTERY, POSITION};

    //! Default constructor
    Alert();

    // Constructor
    Alert(const AlertType &eType, const AlertLevel &eLevel, const QString &sWhat);

    //! Destructor
    ~Alert();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return type
    AlertType type() const;

    //! Return level
    AlertLevel level() const;

    //! Return message
    const QString &what() const;

    //! Return date time
    QString dateTime() const;

private:
    //! Type
    AlertType m_eType = UNDEFINED_ALERT;

    //! Level
    AlertLevel m_eLevel = UNDEFINED_LEVEL;

    //! Message
    QString m_sWhat = "";

    //! Date
    QTime m_dateTime = QTime::currentTime();
};
}

#endif // ALERT_H

// Qt
#include <QDebug>

// Application
#include "alert.h"

//-------------------------------------------------------------------------------------------------

Alert::Alert()
{

}

//-------------------------------------------------------------------------------------------------

Alert::Alert(const DroneBase::AlertType &eType, const DroneBase::Status &eLevel, const QString &sWhat) :
    m_eType(eType), m_eLevel(eLevel), m_sWhat(sWhat), m_dateTime(QTime::currentTime())
{

}

//-------------------------------------------------------------------------------------------------

Alert::~Alert()
{

}

//-------------------------------------------------------------------------------------------------

const DroneBase::AlertType &Alert::type() const
{
    return m_eType;
}

//-------------------------------------------------------------------------------------------------

const DroneBase::Status &Alert::level() const
{
    return m_eLevel;
}

//-------------------------------------------------------------------------------------------------

const QString &Alert::what() const
{
    return m_sWhat;
}

//-------------------------------------------------------------------------------------------------

QString Alert::dateTime() const
{
    return m_dateTime.toString();
}

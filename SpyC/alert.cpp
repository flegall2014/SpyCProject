// Qt
#include <QDebug>

// Application
#include "alert.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

Alert::Alert()
{

}

//-------------------------------------------------------------------------------------------------

Alert::Alert(const AlertType &eType, const AlertLevel &eLevel, const QString &sWhat) :
    m_eType(eType), m_eLevel(eLevel), m_sWhat(sWhat)
{
    m_dateTime = QTime::currentTime();
}

//-------------------------------------------------------------------------------------------------

Alert::~Alert()
{

}

//-------------------------------------------------------------------------------------------------

Alert::AlertType Alert::type() const
{
    return m_eType;
}

//-------------------------------------------------------------------------------------------------

Alert::AlertLevel Alert::level() const
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

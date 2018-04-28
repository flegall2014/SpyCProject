// Application
#include "basesimulator.h"

//-------------------------------------------------------------------------------------------------

BaseSimulator::BaseSimulator(const QString &sDroneUID, QObject *parent) : QObject(parent),
    m_sDroneUID(sDroneUID)
{

}

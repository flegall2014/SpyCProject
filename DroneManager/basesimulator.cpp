// Application
#include "basesimulator.h"
using namespace Model;

//-------------------------------------------------------------------------------------------------

BaseSimulator::BaseSimulator(const QString &sDroneUID, QObject *parent) : QObject(parent),
    m_sDroneUID(sDroneUID)
{

}

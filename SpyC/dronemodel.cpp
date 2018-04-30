// Qt
#include <QDebug>

// Application
#include "dronemodel.h"
#include <dronemanager.h>
#include <drone.h>
#include "dronebase.h"

//-------------------------------------------------------------------------------------------------

DroneModel::DroneModel(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

DroneModel::~DroneModel()
{

}

//-------------------------------------------------------------------------------------------------

void DroneModel::addDrone(DroneBase *pDrone)
{
    qDebug() << "ADDING NEW DRONE " << pDrone->uid();
    if (pDrone != nullptr)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_vDrones << pDrone;
        connect(pDrone, &DroneBase::batteryLevelChanged, this, &DroneModel::onUpdateView, Qt::QueuedConnection);
        connect(pDrone, &DroneBase::positionChanged, this, &DroneModel::onUpdateView, Qt::QueuedConnection);
        endInsertRows();
        emit droneCountChanged();
    }
}

//-------------------------------------------------------------------------------------------------

QVariant DroneModel::data(const QModelIndex &index, int iRole) const
{
    if (iRole == DroneRole)
    {
        if ((index.isValid()) && ((index.row() >= 0) && (index.row() < rowCount())))
            return QVariant::fromValue(m_vDrones[index.row()]);
    }
    return QVariant();
}

//-------------------------------------------------------------------------------------------------

int DroneModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return droneCount();
}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> DroneModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[DroneRole] = "drone";
    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

int DroneModel::droneCount() const
{
    return m_vDrones.size();
}

//-------------------------------------------------------------------------------------------------

void DroneModel::onUpdateView()
{
    DroneBase *pSender = dynamic_cast<DroneBase *>(sender());
    if (pSender != nullptr)
    {
        int iDroneIndex = m_vDrones.indexOf(pSender);
        if (iDroneIndex >= 0)
            emit dataChanged(index(iDroneIndex, 0, QModelIndex()), index(iDroneIndex, 0, QModelIndex()));
    }
}



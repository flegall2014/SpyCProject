// Qt
#include <QDebug>

// Application
#include "droneview.h"
#include <dronemanager.h>
#include <drone.h>
#include "dronebase.h"

//-------------------------------------------------------------------------------------------------

DroneView::DroneView(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

DroneView::~DroneView()
{

}

//-------------------------------------------------------------------------------------------------

void DroneView::addDrone(DroneBase *pDrone)
{
    qDebug() << "ADDING NEW DRONE " << pDrone->uid();
    if (pDrone != nullptr)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_vDrones << pDrone;
        connect(pDrone, &DroneBase::batteryLevelChanged, this, &DroneView::onUpdateView, Qt::QueuedConnection);
        connect(pDrone, &DroneBase::positionChanged, this, &DroneView::onUpdateView, Qt::QueuedConnection);
        endInsertRows();
        emit droneCountChanged();
    }
}

//-------------------------------------------------------------------------------------------------

QVariant DroneView::data(const QModelIndex &index, int iRole) const
{
    if (iRole == DroneRole)
    {
        if ((index.isValid()) && ((index.row() >= 0) && (index.row() < rowCount())))
            return QVariant::fromValue(m_vDrones[index.row()]);
    }
    return QVariant();
}

//-------------------------------------------------------------------------------------------------

int DroneView::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return droneCount();
}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> DroneView::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[DroneRole] = "drone";
    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

int DroneView::droneCount() const
{
    return m_vDrones.size();
}

//-------------------------------------------------------------------------------------------------

void DroneView::onUpdateView()
{
    DroneBase *pSender = dynamic_cast<DroneBase *>(sender());
    if (pSender != nullptr)
    {
        int iDroneIndex = m_vDrones.indexOf(pSender);
        if (iDroneIndex >= 0)
            emit dataChanged(index(iDroneIndex, 0, QModelIndex()), index(iDroneIndex, 0, QModelIndex()));
    }
}



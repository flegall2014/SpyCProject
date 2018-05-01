// Qt
#include <QDebug>

// Application
#include "alertmodel.h"

//-------------------------------------------------------------------------------------------------

AlertModel::AlertModel(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

AlertModel::~AlertModel()
{

}

//-------------------------------------------------------------------------------------------------

void AlertModel::addAlert(const Alert &alert)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_vAlerts << alert;
    endInsertRows();
}

//-------------------------------------------------------------------------------------------------

QVariant AlertModel::data(const QModelIndex &index, int iRole) const
{
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > (m_vAlerts.size()-1)))
        return QVariant();
    if (iRole == AlertType)
        return m_vAlerts[index.row()].type();
    if (iRole == AlertLevel)
        return m_vAlerts[index.row()].level();
    if (iRole == AlertMsg)
        return m_vAlerts[index.row()].what();
    if (iRole == AlertDate)
        return m_vAlerts[index.row()].dateTime();

    return QVariant();
}

//-------------------------------------------------------------------------------------------------

int AlertModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_vAlerts.size();
}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> AlertModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[AlertType] = "type";
    hRoleNames[AlertLevel] = "level";
    hRoleNames[AlertMsg] = "what";
    hRoleNames[AlertDate] = "date";

    return hRoleNames;
}

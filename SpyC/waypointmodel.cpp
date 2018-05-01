// Qt
#include <QDebug>

// Application
#include "waypointmodel.h"

//-------------------------------------------------------------------------------------------------

WayPointModel::WayPointModel(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

WayPointModel::~WayPointModel()
{

}

//-------------------------------------------------------------------------------------------------

int WayPointModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_geoPath.size();
}

//-------------------------------------------------------------------------------------------------

QVariant WayPointModel::data(const QModelIndex &index, int iRole) const
{
    // Check index
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > rowCount()-1))
        return QVariant();

    // Return way point index
    if (iRole == WayPointIndex)
        return index.row();

    // Return way point at index
    if (iRole == WayPointCoordinate)
        return QVariant::fromValue(m_geoPath.coordinateAt(index.row()));

    // Return way point latitude
    if (iRole == WayPointLatitude)
        return m_geoPath.coordinateAt(index.row()).latitude();

    // Return way point at index
    if (iRole == WayPointLongitude)
        return m_geoPath.coordinateAt(index.row()).longitude();

    return QVariant();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::setPointPosition(int iIndex, const QGeoCoordinate &geoCoord)
{
    QModelIndex srcIndex = index(iIndex, 0, QModelIndex());
    if (srcIndex.isValid())
    {
        m_geoPath.replaceCoordinate(iIndex, geoCoord);
        emit dataChanged(srcIndex, srcIndex);
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> WayPointModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[WayPointIndex] = "wayPointIndex";
    hRoleNames[WayPointCoordinate] = "wayPointCoordinate";
    hRoleNames[WayPointLatitude] = "wayPointLatitude";
    hRoleNames[WayPointLongitude] = "wayPointLongitude";

    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

const QGeoPath &WayPointModel::path() const
{
    return m_geoPath;
}

//-------------------------------------------------------------------------------------------------

int WayPointModel::pointCount() const
{
    return m_geoPath.size();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::addCoordinate(const QGeoCoordinate &coordinate)
{
    beginResetModel();
    m_geoPath.addCoordinate(coordinate);
    endResetModel();
    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::removeCoordinateAtIndex(int iCoordIndex)
{
    if ((iCoordIndex >= 0) && (iCoordIndex < rowCount()))
    {
        beginResetModel();
        m_geoPath.removeCoordinate(iCoordIndex);
        endResetModel();
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::clear()
{
    beginResetModel();
    while (!m_geoPath.isEmpty())
        m_geoPath.removeCoordinate(0);
    endResetModel();
    emit pathChanged();
}



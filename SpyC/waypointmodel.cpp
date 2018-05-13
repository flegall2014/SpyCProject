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
    return m_vWayPoints.size();
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
        return QVariant::fromValue(m_vWayPoints[index.row()].geoCoord());

    // Return way point latitude
    if (iRole == WayPointLatitude)
        return m_vWayPoints[index.row()].geoCoord().latitude();

    // Return way point longitude
    if (iRole == WayPointLongitude)
        return m_vWayPoints[index.row()].geoCoord().longitude();

    // Return way point altitude
    if (iRole == WayPointAltitude)
        return m_vWayPoints[index.row()].geoCoord().altitude();

    // Return way point type
    if (iRole == WayPointType)
        return (int)m_vWayPoints[index.row()].type();

    return QVariant();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::setPointPosition(int iIndex, const QGeoCoordinate &geoCoord)
{
    QModelIndex srcIndex = index(iIndex, 0, QModelIndex());
    if (srcIndex.isValid())
    {
        WayPoint currentWayPoint = m_vWayPoints[iIndex];
        currentWayPoint.setGeoCoord(geoCoord);
        m_vWayPoints.replace(iIndex, currentWayPoint);
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
    hRoleNames[WayPointAltitude] = "wayPointAltitude";
    hRoleNames[WayPointLongitude] = "wayPointLongitude";
    hRoleNames[WayPointType] = "wayPointType";

    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

QGeoPath WayPointModel::path()
{
    QGeoPath geoPath;
    foreach (WayPoint wayPoint, m_vWayPoints)
        geoPath.addCoordinate(wayPoint.geoCoord());
    return geoPath;
}

//-------------------------------------------------------------------------------------------------

int WayPointModel::pointCount() const
{
    return m_vWayPoints.size();
}

//-------------------------------------------------------------------------------------------------

int WayPointModel::currentPointIndex() const
{
    return m_iCurrentPointIndex;
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::setCurrentPointIndex(int iIndex)
{
    m_iCurrentPointIndex = iIndex;
    emit currentPointIndexChanged();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::addCoordinate(const QGeoCoordinate &coordinate)
{
    qDebug() << "ADD COORD TO LANDING PLAN " << coordinate;
    beginResetModel();
    m_vWayPoints << WayPoint(coordinate);
    endResetModel();
    emit pathChanged();
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::removeCoordinateAtIndex(int iCoordIndex)
{
    if ((iCoordIndex >= 0) && (iCoordIndex < rowCount()))
    {
        beginResetModel();
        m_vWayPoints.removeAt(iCoordIndex);
        endResetModel();
        emit pathChanged();
    }
}

//-------------------------------------------------------------------------------------------------

void WayPointModel::clear()
{
    beginResetModel();
    m_vWayPoints.clear();
    endResetModel();
    emit pathChanged();
}



// Qt
#include <QDebug>
#include <QGeoCoordinate>

// Application
#include "exclusionareamodel.h"
#include "baseshape.h"

//-------------------------------------------------------------------------------------------------

ExclusionAreaModel::ExclusionAreaModel(QObject *pParent) : QAbstractListModel(pParent)
{

}

//-------------------------------------------------------------------------------------------------

ExclusionAreaModel::~ExclusionAreaModel()
{

}

//-------------------------------------------------------------------------------------------------

QVariant ExclusionAreaModel::data(const QModelIndex &index, int iRole) const
{
    if (!index.isValid())
        return QVariant();
    if ((index.row() < 0) || (index.row() > rowCount()-1))
        return QVariant();
    if (iRole == ShapeRole)
        return QVariant::fromValue(m_vShapes[index.row()]);
    return QVariant();
}

//-------------------------------------------------------------------------------------------------

int ExclusionAreaModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_vShapes.size();
}

//-------------------------------------------------------------------------------------------------

QHash<int, QByteArray> ExclusionAreaModel::roleNames() const
{
    QHash<int, QByteArray> hRoleNames;
    hRoleNames[ShapeRole] = "shape";
    return hRoleNames;
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addShape(BaseShape *pShape)
{
    if (pShape != nullptr)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_vShapes << pShape;
        endInsertRows();
    }
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addRectangle(const QGeoCoordinate &center)
{
    QGeoCoordinate topLeft = center.atDistanceAndAzimuth(DEFAULT_RADIUS, 135);
    QGeoCoordinate bottomRight = center.atDistanceAndAzimuth(DEFAULT_RADIUS, -45);
    RectangleShape *pShape = new RectangleShape(topLeft, bottomRight, this);
    addShape(pShape);
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addCircle(const QGeoCoordinate &center)
{
    CircleShape *pShape = new CircleShape(center, DEFAULT_RADIUS);
    addShape(pShape);
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::addTriangle(const QGeoCoordinate &center)
{
    QGeoCoordinate point1 = center.atDistanceAndAzimuth(DEFAULT_RADIUS, 90);
    QGeoCoordinate point2 = center.atDistanceAndAzimuth(DEFAULT_RADIUS, 210);
    QGeoCoordinate point3 = center.atDistanceAndAzimuth(DEFAULT_RADIUS, 330);
    TriangleShape *pShape = new TriangleShape(point1, point2, point3);
    addShape(pShape);
}

//-------------------------------------------------------------------------------------------------

void ExclusionAreaModel::clear()
{
    beginResetModel();
    qDeleteAll(m_vShapes);
    m_vShapes.clear();
    endResetModel();
}
